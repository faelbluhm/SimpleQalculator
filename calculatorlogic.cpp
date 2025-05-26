// calculatorlogic.cpp
#include "calculatorlogic.h"
#include <cmath>
#include <QDebug>

static const char* ERROR_OUT_OF_BOUNDS = "Error: OB";
static const char* ERROR_DIV_0 = "Error: DIV 0";
static const char* ERROR_NEGATIVE_SQUARE = "Error: √-";
static const char* ERROR_INF = "Error: Inf";

/*!
 * \class CalculatorLogic
 * \brief Handles the core logic of a simple calculator.
 *
 * This class handles numeric input, arithmetic operations, error states,
 * and updates the display accordingly. It is designed to be connected to
 * a QML frontend using Qt's signal-slot system.
 */

CalculatorLogic::CalculatorLogic(QObject *parent)
    : QObject(parent), m_displayText("0") {}

QString CalculatorLogic::displayText() const {
  return m_displayText;
}

QString CalculatorLogic::currentOperator() const {
  return m_currentOperator;
}

/*!
 * \brief Updates the calculator display and emits change signal.
 */
void CalculatorLogic::updateDisplay(const QString &text) {
  if (text.length() > m_displayLength) {
    setError(ERROR_OUT_OF_BOUNDS);
  } else if (text == "inf") {
    setError(ERROR_INF);
  }
  else {
    m_displayText = text;
    emit displayTextChanged();
  }
}

/*!
 * \brief Sets an error message and flags the error state.
 */
void CalculatorLogic::setError(const QString &errorMessage) {
  m_displayText = errorMessage;
  m_hasError = true;
  emit displayTextChanged();
}

/*!
 * \brief Resets all internal states and clears the display.
 */
void CalculatorLogic::clear() {
  m_displayText = "0";
  m_lastOperand = 0.0;
  m_hasError = false;
  m_hasCleared = true;
  m_startNewNumber = false;
  m_isFirstInput = true;
  m_currentOperator.clear();
  m_pendingOperation.clear();
  emit currentOperatorChanged();
  emit displayTextChanged();
}

/*!
 * \brief Deletes the last digit or resets to zero if only one remains.
 */
void CalculatorLogic::deleteDigit() {
  if (m_hasError) return;

  if (m_displayText.length() == 1 ||
      (m_displayText.startsWith('-') && m_displayText.length() == 2)) {
    updateDisplay("0");
  } else {
    if (m_displayText.endsWith("."))
      m_displayText.chop(1);
    m_displayText.chop(1);
    updateDisplay(m_displayText);
  }
}

/*!
 * \brief Appends a digit to the current display text.
 */
void CalculatorLogic::handleDigit(const QString &digit) {
  if (m_hasError) return;
  m_isFirstInput = false;

  if (m_startNewNumber || m_hasCleared || m_displayText == "0") {
    m_displayText = digit;
    m_startNewNumber = false;
    m_hasCleared = false;
  } else if (m_displayText.length() < m_displayLength) {
    m_displayText += digit;
  }

  updateDisplay(m_displayText);
}

/*!
 * \brief Handles the decimal point input.
 */
void CalculatorLogic::handleDot() {
  if (m_hasError) return;

  if (m_startNewNumber) {
    m_displayText = "0.";
    m_startNewNumber = false;
  } else if (!m_displayText.contains(".")) {
    m_displayText += ".";
  }

  m_hasCleared = false;
  updateDisplay(m_displayText);
}

/*!
 * \brief Handles arithmetic and special operations.
 */
void CalculatorLogic::handleOperator(const QString &operation) {
  if (m_hasError || m_isFirstInput) return;

  if (operation == "sqrt" || operation == "square" || operation == "percent") {
    performOperation(operation);
    updateDisplay(m_displayText);
  }
  else if (operation == "add" || operation == "subtract" ||
           operation == "multiply" || operation == "divide") {

    if (!m_pendingOperation.isEmpty() && !m_startNewNumber) {
      performOperation(m_pendingOperation);
      updateDisplay(m_displayText);
    } else {
      m_lastOperand = m_displayText.toDouble();
    }

    m_pendingOperation = operation;
    m_currentOperator = operation;
    emit currentOperatorChanged();
    m_startNewNumber = true;
  }
  else if (operation == "calculate") {
    performOperation(m_pendingOperation);
    updateDisplay(m_displayText);
    m_startNewNumber = true;
    m_currentOperator.clear();
    emit currentOperatorChanged();
  }
}

/*!
 * \brief Executes the current pending operation and updates the result.
 */
void CalculatorLogic::performOperation(const QString &operation) {
  double operand = m_displayText.toDouble();
  double result = 0.0;

  if (operation == "square") {
    operand *= operand;
    m_displayText = QString::number(operand);
    return;
  }

  if (operation == "sqrt") {
    if (operand < 0) {
      setError(ERROR_NEGATIVE_SQUARE);
      return;
    }
    m_displayText = QString::number(std::sqrt(operand));
    return;
  }

  if (operation == "percent") {
    if (!m_pendingOperation.isEmpty()) {
      operand = m_lastOperand * operand / 100.0;
    } else {
      operand /= 100.0;
    }
    m_displayText = QString::number(operand);
    return;
  }

         // Binary operations
  if (m_pendingOperation == "add") {
    result = m_lastOperand + operand;
  } else if (m_pendingOperation == "subtract") {
    result = m_lastOperand - operand;
  } else if (m_pendingOperation == "multiply") {
    result = m_lastOperand * operand;
  } else if (m_pendingOperation == "divide") {
    if (operand == 0.0) {
      setError(ERROR_DIV_0);
      return;
    }
    result = m_lastOperand / operand;
  } else {
    result = operand;
  }

  m_lastOperand = result;
  m_displayText = QString::number(result);
  m_pendingOperation.clear();
}

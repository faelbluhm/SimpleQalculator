#ifndef CALCULATORLOGIC_H
#define CALCULATORLOGIC_H

#include <QObject>
#include <QString>

/*!
 * \class CalculatorLogic
 * \brief Handles the business logic for a basic calculator application.
 *
 * This class processes user inputs (digits, operations, etc.), performs
 * arithmetic computations, manages display state, and handles error cases.
 * It is designed to integrate with a QML interface via Q_PROPERTY and Q_INVOKABLE.
 */
class CalculatorLogic : public QObject {
  Q_OBJECT

         // Display text shown on calculator screen
  Q_PROPERTY(QString displayText READ displayText NOTIFY displayTextChanged)

         // Operator currently in use (used to highlight operator buttons)
  Q_PROPERTY(QString currentOperator READ currentOperator NOTIFY currentOperatorChanged)

public:
  explicit CalculatorLogic(QObject *parent = nullptr);

         /// Returns the current display text
  QString displayText() const;

         /// Returns the current operator symbol (if any)
  QString currentOperator() const;

         /// Resets calculator state and display
  Q_INVOKABLE void clear();

         /// Deletes the last digit or resets to 0 if empty
  Q_INVOKABLE void deleteDigit();

         /// Handles input of a single digit (0-9)
  Q_INVOKABLE void handleDigit(const QString &digit);

         /// Handles input of decimal point
  Q_INVOKABLE void handleDot();

         /// Handles calculator operations (add, subtract, sqrt, etc.)
  Q_INVOKABLE void handleOperator(const QString &op);

signals:
  void displayTextChanged();       ///< Emitted when the display text changes
  void currentOperatorChanged();   ///< Emitted when the operator changes

private:
  /// Updates the display safely, validating length
  void updateDisplay(const QString &text);

         /// Performs the operation stored in `op` and updates result
  void performOperation(const QString &op);

         /// Sets an error message and flags error state
  void setError(const QString &message);

         // --- Internal state ---
  QString m_displayText = "0";          ///< Text shown on display
  int m_displayLength = 15;             ///< Max number of characters allowed
  bool m_hasError = false;              ///< Whether the calculator is in an error state
  bool m_hasCleared = true;             ///< Whether the calculator was just cleared
  bool m_startNewNumber = false;        ///< Whether the next digit starts a new number
  double m_lastOperand = 0.0;           ///< Last operand used in calculation
  QString m_pendingOperation = "";      ///< Pending binary operation (e.g., "add")
  QString m_currentOperator = "";       ///< Currently active operator (for UI)
  bool m_isFirstInput = true;           ///< Whether this is the first input after launch or reset
};

#endif // CALCULATORLOGIC_H

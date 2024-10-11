using System.Collections.Generic;
using System;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebApplication3
{
    public class Calculadora
    {
        // Método para evaluar expresiones infijas
        public double EvaluateInfix(string expression)
        {
            string postfixExpression = ConvertInfixToPostfix(expression);
            return EvaluatePostfix(postfixExpression);
        }

        // Método para evaluar expresiones prefijas
        public double EvaluatePrefix(string expression)
        {
            Stack<double> stack = new Stack<double>();
            string[] tokens = expression.Split(' ');

            // Recorrer los tokens desde el final
            for (int i = tokens.Length - 1; i >= 0; i--)
            {
                string token = tokens[i];

                double number;
                if (double.TryParse(token, out number))
                {
                    // Si es un número, lo añadimos a la pila
                    stack.Push(number);
                }
                else
                {
                    // Si es un operador, sacar dos operandos de la pila
                    double operand1 = stack.Pop();
                    double operand2 = stack.Pop();

                    // Aplicar la operación y almacenar el resultado
                    stack.Push(ApplyOperation(token, operand1, operand2));
                }
            }

            return stack.Pop(); // El resultado final
        }

        // Convertir expresión infija a postfija (usando algoritmo de Shunting Yard)
        private string ConvertInfixToPostfix(string expression)
        {
            Stack<string> operators = new Stack<string>();
            List<string> output = new List<string>();
            string[] tokens = expression.Split(' ');

            foreach (string token in tokens)
            {
                double number;
                if (double.TryParse(token, out number))
                {
                    output.Add(token); // Si es un número, agregarlo a la salida
                }
                else if (token == "(")
                {
                    operators.Push(token); // Si es un paréntesis izquierdo, apilarlo
                }
                else if (token == ")")
                {
                    // Desapilar operadores hasta encontrar el paréntesis izquierdo
                    while (operators.Count > 0 && operators.Peek() != "(")
                    {
                        output.Add(operators.Pop());
                    }
                    operators.Pop(); // Eliminar el paréntesis izquierdo
                }
                else if (IsOperator(token))
                {
                    while (operators.Count > 0 && Priority(operators.Peek()) >= Priority(token))
                    {
                        output.Add(operators.Pop());
                    }
                    operators.Push(token);
                }
            }

            // Desapilar los operadores restantes
            while (operators.Count > 0)
            {
                output.Add(operators.Pop());
            }

            return string.Join(" ", output); // Retornar expresión en notación postfija
        }

        // Evaluar expresión en notación postfija
        private double EvaluatePostfix(string expression)
        {
            Stack<double> stack = new Stack<double>();
            string[] tokens = expression.Split(' ');

            foreach (string token in tokens)
            {
                double number;
                if (double.TryParse(token, out number))
                {
                    stack.Push(number);
                }
                else
                {
                    double operand2 = stack.Pop();
                    double operand1 = stack.Pop();
                    stack.Push(ApplyOperation(token, operand1, operand2));
                }
            }

            return stack.Pop();
        }

        // Aplicar operación (+, -, *, /)
        private double ApplyOperation(string operation, double operand1, double operand2)
        {
            switch (operation)
            {
                case "+":
                    return operand1 + operand2;
                case "-":
                    return operand1 - operand2;
                case "*":
                    return operand1 * operand2;
                case "/":
                    return operand1 / operand2;
                default:
                    throw new ArgumentException("Operador inválido");
            }
        }

        // Verificar si es un operador
        private bool IsOperator(string token)
        {
            return token == "+" || token == "-" || token == "*" || token == "/";
        }

        // Asignar prioridad a los operadores
        private int Priority(string operation)
        {
            switch (operation)
            {
                case "+":
                case "-":
                    return 1;
                case "*":
                case "/":
                    return 2;
                default:
                    return 0;
            }
        }
    }
}
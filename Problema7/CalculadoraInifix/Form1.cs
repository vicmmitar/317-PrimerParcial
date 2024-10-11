using CalculatorLibrary;
using System.Linq.Expressions;

namespace CalculadoraInifix
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, EventArgs e)
        {
            Button boton = sender as Button;
            if (boton != null)
            {

                if (resultado == 0 && char.IsDigit(boton.Text, 0))
                    textBox1.Clear();

                textBox1.Text += boton.Text + " ";
            }
        }

        public int resultado = 2;

        private void button15_Click(object sender, EventArgs e)
        {
            Calculadora calc = new Calculadora();
            try
            {
                string expresionInfija = textBox1.Text;
                expresionInfija = expresionInfija.Trim();

                //MessageBox.Show(expresionInfija);
                double resultInfix = calc.EvaluateInfix(expresionInfija);
                textBox1.Text = resultInfix.ToString() + " ";
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error en la expresión: " + ex.Message);
            }
        }

        private void button16_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
        }
    }
}

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnDetectEdges_Click(object sender, EventArgs e)
        {
            // Cargar la imagen original desde el PictureBox
            Bitmap originalImage = new Bitmap(pictureBox1.Image);

            // Convertir a escala de grises
            Bitmap grayImage = ConvertToGrayscale(originalImage);

            // Aplicar filtro Sobel para detectar bordes
            Bitmap edgeImage = ApplySobelFilter(grayImage);

            // Mostrar la imagen con los bordes detectados en otro PictureBox
            pictureBox2.Image = edgeImage;
        }

        // Método para convertir la imagen a escala de grises
        private Bitmap ConvertToGrayscale(Bitmap original)
        {
            Bitmap grayImage = new Bitmap(original.Width, original.Height);

            for (int y = 0; y < original.Height; y++)
            {
                for (int x = 0; x < original.Width; x++)
                {
                    // Obtener el color del píxel
                    Color originalColor = original.GetPixel(x, y);

                    // Convertir el color a escala de grises usando la fórmula de luminosidad
                    int grayValue = (int)((originalColor.R * 0.3) + (originalColor.G * 0.59) + (originalColor.B * 0.11));

                    // Crear un nuevo color gris
                    Color grayColor = Color.FromArgb(grayValue, grayValue, grayValue);

                    // Establecer el píxel en la imagen en escala de grises
                    grayImage.SetPixel(x, y, grayColor);
                }
            }

            return grayImage;
        }

        // Método para aplicar el filtro Sobel
        private Bitmap ApplySobelFilter(Bitmap grayImage)
        {
            Bitmap edgeImage = new Bitmap(grayImage.Width, grayImage.Height);

            // Definir los kernels de Sobel para detección de bordes
            int[,] sobelX = new int[,]
            {
                { -1, 0, 1 },
                { -2, 0, 2 },
                { -1, 0, 1 }
            };

            int[,] sobelY = new int[,]
            {
                { -1, -2, -1 },
                {  0,  0,  0 },
                {  1,  2,  1 }
            };

            // Aplicar Sobel
            for (int y = 1; y < grayImage.Height - 1; y++)
            {
                for (int x = 1; x < grayImage.Width - 1; x++)
                {
                    int pixelX = 0;
                    int pixelY = 0;

                    // Aplicar las matrices de Sobel
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            Color pixelColor = grayImage.GetPixel(x + j, y + i);
                            int grayValue = pixelColor.R;

                            pixelX += grayValue * sobelX[i + 1, j + 1];
                            pixelY += grayValue * sobelY[i + 1, j + 1];
                        }
                    }

                    // Calcular la magnitud del gradiente
                    int gradientMagnitude = (int)Math.Sqrt((pixelX * pixelX) + (pixelY * pixelY));

                    // Asegurarse de que el valor esté entre 0 y 255
                    gradientMagnitude = Math.Min(255, Math.Max(0, gradientMagnitude));

                    // Establecer el nuevo valor en la imagen de bordes
                    Color edgeColor = Color.FromArgb(gradientMagnitude, gradientMagnitude, gradientMagnitude);
                    edgeImage.SetPixel(x, y, edgeColor);
                }
            }

            return edgeImage;
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Archivos png|*png|Archivos jpg|*jpg";
            openFileDialog1.ShowDialog();
            Bitmap bmp = new Bitmap(openFileDialog1.FileName);
            pictureBox1.Image = bmp;
        }
    }
}

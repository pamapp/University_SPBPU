using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ModelSystemSpecialEventMethod
{
    public partial class Auto : Form
    {
       // private float workloadDevice = 0.7f;
       // private float Pfailure = 0.1f;
       // private float Pworkload = 0.05f; //Pзагруженность

        private string filePath = @"C:\Users\Викушка\Desktop\Ежиха\Var16CMO-20211216T161522Z-001\Var16CMO\ModelSystemSpecialEventMethodVar8\ModelSystemSpecialEventMethod\PrevTests.txt";


        public Auto()
        {
           // this.workloadDevice = workloadDevice;
           // this.Pfailure = Pfailure;
            InitializeComponent();

            dataGridView1.ColumnCount = 2;
            dataGridView1.Columns[0].HeaderText = "Параметр";
            dataGridView1.Columns[1].HeaderText = "Значение";
            dataGridView1.Columns[0].Width = 260;
            dataGridView1.Columns[1].AutoSizeMode = (DataGridViewAutoSizeColumnMode)DataGridViewAutoSizeColumnsMode.Fill;
            
            dataGridView2.ColumnCount = 2;
            dataGridView2.Columns[0].HeaderText = "Параметр";
            dataGridView2.Columns[1].HeaderText = "Значение";
            dataGridView2.Columns[0].Width = 260;
            dataGridView2.Columns[1].AutoSizeMode = (DataGridViewAutoSizeColumnMode)DataGridViewAutoSizeColumnsMode.Fill;

        }

        private void Auto_Load(object sender, EventArgs e)
        {
            // сравниваем пред Pзагруженность с текущей она не должна отличаться более чем на 10 процентов
            
                Program.AutoMode();

            //float PrevWorkload = Program.Pworkload;

            ////Если х> у, тогда разница r вычисляется по формуле:

            ////    r = ((x - y) / x) * 100

            ////        Если х<y,

            ////    r= ((y - x) / x) * 100.



            //Program.totalRequestGenerate = Program.random.Next(100, 2000);

            //Program.StepMode();
            //float currentWorkload = Program.Pworkload;

            //float r = -1;

            //if (PrevWorkload > currentWorkload)
            //{
            //    r = ((PrevWorkload - currentWorkload) / PrevWorkload);
            //} else
            //{
            //    r = (currentWorkload - PrevWorkload) / PrevWorkload;
            //}

            //int i = 0;
            //while (r > Pfailure)
            //{

            //    Program.StepMode();

            //    PrevWorkload = currentWorkload;
            //    currentWorkload = Program.Pworkload;

            //    if (PrevWorkload > currentWorkload)
            //    {
            //        r = (((PrevWorkload - currentWorkload) / PrevWorkload)) * 100;
            //    }
            //    else
            //    {
            //        r = ((currentWorkload - PrevWorkload) / PrevWorkload) * 100;
            //    }

            //    Program.totalRequestGenerate = Program.random.Next(100, 1000);

            //    //if (i == 25)
            //    //{
            //    //    break;
            //    //}
            //    i++;
            //}
            printPreviousResults();

            printResults();

          
            
        }

        private void printPreviousResults()
        {
           string docPath = Directory.GetCurrentDirectory();
           //Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            using (StreamReader sr = new StreamReader(filePath))
            {
                string line = null;
                while ((line = sr.ReadLine()) != null && line != "-----")
                {
                    StringBuilder parameter = new StringBuilder(16);
                    StringBuilder resultOfParameter = new StringBuilder(26);
                    bool wasSeparator = false;
                    for (int j = 0; j < line.Length; j++)
                    {
                        if (line[j] == ':')
                        {
                            wasSeparator = true;
                            continue;
                        }
                        if (!wasSeparator)
                        {
                            parameter.Append(line[j]);
                        }
                        else
                        {
                            resultOfParameter.Append(line[j]);
                        }

                    }

                    dataGridView2.Rows.Add(parameter, resultOfParameter);
                    
                    //listBox2.Items.Add(line);
                }
                
            }
        }

        private void printResults()
        {

            // так же напечатать параметры системы

            dataGridView1.Rows.Add("Количество источников: ", Program.amountSouce);
            dataGridView1.Rows.Add("Размер буфера: ", Program.bufferSize);
            dataGridView1.Rows.Add("Количество приборов: ", Program.amountDevice);

            for (int i = 0; i < Program.finalResults.Count(); i++)
            {

                StringBuilder parameter = new StringBuilder(16);
                StringBuilder resultOfParameter = new StringBuilder(26);
                string line = Program.finalResults[i];
                bool wasSeparator = false;
                for (int j = 0; j < line.Length; j++)
                {
                    if (line[j] == ':')
                    {
                        wasSeparator = true;
                        continue;
                    }
                    if (!wasSeparator)
                    {
                        parameter.Append(line[j]);
                    }
                    else
                    {
                        resultOfParameter.Append(line[j]);
                    }

                }

                dataGridView1.Rows.Add(parameter, resultOfParameter);
               
            }

            SaveResultsToFile();
        }

        private void SaveResultsToFile()
        {
            // Set a variable to the Documents path.
            
            // Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);


            // Write the string array to a new file named "WriteLines.txt".
            using (StreamWriter outputFile = new StreamWriter(filePath))
            {
                outputFile.WriteLine("Количество источников: " + Program.amountSouce);
                outputFile.WriteLine("Размер буфера: " + Program.bufferSize);
                outputFile.WriteLine("Количество приборов: " + Program.amountDevice);
                foreach (string line in Program.finalResults)
                    outputFile.WriteLine(line);

                outputFile.WriteLine();
                outputFile.Write("-----");
            }
        
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}

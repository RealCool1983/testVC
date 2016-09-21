using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace LoadDLLTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        

        private void button1_Click(object sender, EventArgs e)
        {
            string CurrDir = System.IO.Directory.GetCurrentDirectory();
            string DBDLLFilePath = CurrDir + "\\QisdaDLL\\QisdaTool.dll";

            if (File.Exists(DBDLLFilePath) == false)
            {
                // textBox1.BackColor = Color.Pink;
               // Label3.Text = "ERROR: DB DLL isn't exist.";

            }
            string m_str_DB_Server;
            string m_str_DB_Account;
            string m_str_DB_Password;

            bool isOk = true;
            string Msg = "";
            string sText = "";
            sText += "";
            IntPtr pDll = NativeMethods.LoadLibrary(@DBDLLFilePath);
            //oh dear, error handling here
            //if (pDll == IntPtr.Zero)

            IntPtr pAddressOfFunctionToCall1 = NativeMethods.GetProcAddress(pDll, "ProductInfoAccess");

            label1.Text = Marshal.GetLastWin32Error().ToString();
            IntPtr pAddressOfFunctionToCall = NativeMethods.GetProcAddress(pDll, "PCBAInfo");


        }
        static class NativeMethods
        {

            //[DllImport("kernel32.dll", CharSet=CharSet.Ansi, ExactSpelling=true, SetLastError=true)]
            [DllImport("kernel32.dll")]
            public static extern IntPtr LoadLibrary(string dllToLoad);

            [DllImport("kernel32.dll",  SetLastError = true)]
            public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);



            [DllImport("kernel32.dll")]
            public static extern bool FreeLibrary(IntPtr hModule);
        }

    }

}

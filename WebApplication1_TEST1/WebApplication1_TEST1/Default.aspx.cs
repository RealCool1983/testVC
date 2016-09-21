using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Security.Cryptography;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;

namespace WebApplication1_TEST1
{
    public partial class _Default : System.Web.UI.Page
    {

        private static string IV = "IV_VALUE_16_BYTE";
       // private static string IV = "12345678912345";
        private static string PASSWORD = "PASSWORD_VALUE";
        private static string SALT = "SALT_VALUE";
        private static string keykey = "1234567891234567";

        protected void Page_Load(object sender, EventArgs e)
        {
        }
        protected void Create_Click(object sender, EventArgs e)
        {
            byte[] byte_source;
            byte[] byte_md5_crypto;
            string result;
            string sInput;
            sInput = input.Text + input0.Text + input1.Text + input2.Text;
            MD5 md5 = MD5.Create();//建立一個MD5


            byte_source = Encoding.UTF8.GetBytes(input.Text);//將字串轉為Byte[]
            byte_md5_crypto = md5.ComputeHash(byte_source);//進行MD5加密
            result = Convert.ToBase64String(byte_md5_crypto);//把加密後的字串從Byte[]轉為字串
            //Response.Write("MD5加密:  \r" + result);//輸出結果
            SOMKEY.Text = (result);

            byte_source = Encoding.Default.GetBytes(sInput);//將字串轉為Byte[]
            byte_md5_crypto = md5.ComputeHash(byte_source);//進行MD5加密
            result = Convert.ToBase64String(byte_md5_crypto);//把加密後的字串從Byte[]轉為字串
            //     result = Convert.ToString(byte_md5_crypto);//把加密後的字串從Byte[]轉為字串
            //Response.Write("MD5加密:  \r" + result);//輸出結果
            LKEY.Text = (result);

            //12490306
            string sFinalKey;
            sFinalKey = result.Substring(1, 1) + result.Substring(2, 1) + result.Substring(4, 1) + result.Substring(9, 1) + result.Substring(0, 1) + result.Substring(3, 1) + result.Substring(0, 1) + result.Substring(6, 1);
            LKEY0.Text = (sFinalKey);

            //-----------------------------------
            byte_source = Encoding.Default.GetBytes(input0.Text);//將字串轉為Byte[]
            byte_md5_crypto = md5.ComputeHash(byte_source);//進行MD5加密
            result = Convert.ToBase64String(byte_md5_crypto);//把加密後的字串從Byte[]轉為字串
            ABOKEY.Text = (result);

            byte_source = Encoding.Default.GetBytes(input1.Text);//將字串轉為Byte[]
            byte_md5_crypto = md5.ComputeHash(byte_source);//進行MD5加密
            result = Convert.ToBase64String(byte_md5_crypto);//把加密後的字串從Byte[]轉為字串
            //Response.Write("MD5加密:  \r" + result);//輸出結果
            BBOKEY.Text = (result);

            byte_source = Encoding.Default.GetBytes(input2.Text);//將字串轉為Byte[]
            byte_md5_crypto = md5.ComputeHash(byte_source);//進行MD5加密
            //result = Convert.ToBase64String(crypto);//把加密後的字串從Byte[]轉為字串
            result = Convert.ToBase64String(byte_md5_crypto);//把加密後的字串從Byte[]轉為字串
            //Response.Write("MD5加密:  \r" + result);//輸出結果
            WIFIKEY.Text = (result);

        }

        public string makeMd5(string sString)
        {
            string sResult = "NULL";
            byte[] byte_source;
            byte[] byte_md5_crypto;
            MD5 md5 = MD5.Create();//建立一個MD5

            byte_source = Encoding.Default.GetBytes(sString);//將字串轉為Byte[]
            byte_md5_crypto = md5.ComputeHash(byte_source);//進行MD5加密
           
            StringBuilder sBuilder = new StringBuilder();
            // Loop through each byte of the hashed data 
            // and format each one as a hexadecimal string.
            for (int i = 0; i < byte_md5_crypto.Length; i++)
            {
                sBuilder.Append(byte_md5_crypto[i].ToString("x2"));
            }
            sResult = sBuilder.ToString();
            //Response.Write("MD5加密:  \r" + result);//輸出結果
           // ABOKEY.Text = (result);

            return sResult;

        }

        public static string EncryptAndEncode(string raw)
        {
            using (var csp = new AesCryptoServiceProvider())
            {
                ICryptoTransform e = GetCryptoTransform(csp, true);
                byte[] inputBuffer = Encoding.UTF8.GetBytes(raw);
                byte[] output = e.TransformFinalBlock(inputBuffer, 0, inputBuffer.Length);
                string encrypted = Convert.ToBase64String(output);
                return encrypted;
            }
        }

        public static string DecodeAndDecrypt(string encrypted)
        {
            using (var csp = new AesCryptoServiceProvider())
            {
                var d = GetCryptoTransform(csp, false);
                byte[] output = Convert.FromBase64String(encrypted);

                byte[] decryptedOutput = d.TransformFinalBlock(output, 0, output.Length);
                string decypted = Encoding.UTF8.GetString(decryptedOutput);
                return decypted;

               }
        } 
        private static ICryptoTransform GetCryptoTransform(AesCryptoServiceProvider csp, bool encrypting)
        {
            csp.Mode = CipherMode.CBC;
            csp.Padding = PaddingMode.PKCS7;
            //var spec = new Rfc2898DeriveBytes(Encoding.UTF8.GetBytes(PASSWORD), Encoding.UTF8.GetBytes(SALT), 65536);
           //byte[] key = spec.GetBytes(16);
           //csp.Key = key;
            // key-block combinations with sizes of 128-128, 192-128, and 256-128 bits.
            //So the block size is always 128-bits.
            
            csp.KeySize = 256;
            csp.BlockSize = 128;
            
            
            csp.IV = Encoding.UTF8.GetBytes(IV);
            csp.Key = Encoding.UTF8.GetBytes(keykey);

          //  csp.KeySize = 256;
            
            if (encrypting)
            {
                return csp.CreateEncryptor();
            }
            return csp.CreateDecryptor();
        }


        public bool checkTextBoxEmpty()
        {
            bool bRes = false;
             if (string.IsNullOrEmpty(input.Text.Trim())) {
                 MSG.Text = "input is empty";
                 bRes = false;
             }
             else if  (string.IsNullOrEmpty(input0.Text.Trim())) 
             {
                 MSG.Text = "input0 is empty";
                 bRes = false;            
             }
             else if  (string.IsNullOrEmpty(input1.Text.Trim())) 
             {
                 MSG.Text = "input1 is empty";
                 bRes = false;            
             }
             else if (string.IsNullOrEmpty(input2.Text.Trim()))
             {
                 MSG.Text = "input2 is empty";
                 bRes = false;
             }
             else
             {
                 MSG.Text = "Input ok";
                 bRes = true ;
             }
            return bRes;
        }

      

        protected void Create_Click_MD5(object sender, EventArgs e)
        {
            byte[] source;
            byte[] crypto;
            string result = "NULL";
            string sInput = "NULL";

            if (checkTextBoxEmpty())
            {
                sInput = input.Text.Trim() + input0.Text.Trim() + input1.Text.Trim() + input2.Text.Trim();
                Label2.Text = sInput;
                SOMKEY.Text = makeMd5(input.Text);
                ABOKEY.Text = makeMd5(input0.Text);
                BBOKEY.Text = makeMd5(input1.Text);
                WIFIKEY.Text = makeMd5(input2.Text);
                result = makeMd5(sInput);

                LKEY.Text = (result);
                //12490306
                string sFinalKey;
                sFinalKey = result.Substring(1, 1) + result.Substring(2, 1) + result.Substring(4, 1) + result.Substring(9, 1) + result.Substring(0, 1) + result.Substring(3, 1) + result.Substring(0, 1) + result.Substring(6, 1);
                LKEY0.Text = (sFinalKey);
            }
        }

        protected void Button3_Click(object sender, EventArgs e)
        {
            byte[] source;
            byte[] crypto;
            string result = "NULL";
            string sInput = "NULL";

            if (checkTextBoxEmpty())
            {
                sInput = input.Text + input0.Text + input1.Text + input2.Text;
                Label2.Text = sInput;
                SOMKEY.Text = EncryptAndEncode(input.Text);
                ABOKEY.Text = EncryptAndEncode(input0.Text);
                BBOKEY.Text = EncryptAndEncode(input1.Text);
                WIFIKEY.Text = EncryptAndEncode(input2.Text);
                result = EncryptAndEncode(sInput);
               

                LKEY.Text = (result);
                //12490306
                string sFinalKey;
                sFinalKey = result.Substring(1, 1) + result.Substring(2, 1) + result.Substring(4, 1) + result.Substring(9, 1) + result.Substring(0, 1) + result.Substring(3, 1) + result.Substring(0, 1) + result.Substring(6, 1);
                LKEY0.Text = (sFinalKey);
            }
        }
        //DllImport 
        static class NativeMethods
        {
            
                //[DllImport("kernel32.dll", CharSet=CharSet.Ansi, ExactSpelling=true, SetLastError=true)]
                [DllImport("kernel32.dll")]
                public static extern IntPtr LoadLibrary(string dllToLoad);

                [DllImport("kernel32.dll")]
                public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);



                [DllImport("kernel32.dll")]
                public static extern bool FreeLibrary(IntPtr hModule);
        }

        QisdaTool.ProductInfo NowProductInfo;
        List<QisdaTool.PCBAInfo> ApolloPCBAInfo = new List<QisdaTool.PCBAInfo>();
        /// <summary>
        /// 資料庫讀取與寫入物件，創建時必須給定(主機路徑,登入帳號,登入密碼)
        /// </summary>
        QisdaTool.ProductInfoAccess Accsess = new QisdaTool.ProductInfoAccess("QTYSMARTSQL01.benq.corp.com\\QTYSF", "Qisdard", "Qisdard");

        protected void Button4_Click(object sender, EventArgs e)
        {
            string CurrDir = System.IO.Directory.GetCurrentDirectory();
            string DBDLLFilePath = CurrDir + "\\QisdaDLL\\QisdaToolPara.ini";
            
            if (File.Exists(DBDLLFilePath) == false)
            {
                // textBox1.BackColor = Color.Pink;
                Label3.Text = "ERROR: DB DLL isn't exist.";

            }

            string stmp = "N19892460704112815";
            string ErrorMessage = "";
            ///將機台TRID輸入，創建一個物件
            NowProductInfo = new QisdaTool.ProductInfo(stmp);

            ///資料庫連線檢查
            if (Accsess.DataBaseConnectCheck(out ErrorMessage) == false)
            {
                string stmp1 = "error";
                //MessageBox.Show(ErrorMessage, "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            ///取PCBA ID範例如下
            ///
            if (Accsess.GetPCBAIDandSN(stmp, ref ApolloPCBAInfo, DBDLLFilePath, out ErrorMessage) == false)
            {
                string stmp2 = "error";
                //MessageBox.Show(ErrorMessage, "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

           // string CurrDir = System.IO.Directory.GetCurrentDirectory();
            //string DBDLLFilePath = CurrDir + "\\QisdaDLL\\QisdaTool.dll";

            if (File.Exists(DBDLLFilePath) == false)
            {
               // textBox1.BackColor = Color.Pink;
                    Label3.Text = "ERROR: DB DLL isn't exist.";

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
               IntPtr pAddressOfFunctionToCall = NativeMethods.GetProcAddress(pDll, "PCBAInfo");

//public bool GetPCBAIDandSN(string ApolloTRID, ref List<PCBAInfo> PCBAInfoList, string ApplicationPath, out string ErrorMessage)
            //Accsess = new QisdaTool.ProductInfoAccess(m_str_DB_Server, m_str_DB_Account, m_str_DB_Password);
            //isOk = Accsess.DataBaseConnectCheck(out Msg);
            //break;
            //string sTmp = DecodeAndDecrypt(LKEY0.Text);
          //  LKEY1.Text = DecodeAndDecrypt(LKEY.Text);
            //  DllImport("msvcrt.dll");
        }
    }
}

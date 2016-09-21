using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 目前機台資訊(包含ModelName,料號,工廠流線ID號碼,TRID號碼)
        /// </summary>
        QisdaTool.ProductInfo NowProductInfo;


        /// <summary>
        /// 宣告存放PCBA資料物件
        /// </summary>
        List<QisdaTool.PCBAInfo> ApolloPCBAInfo = new List<QisdaTool.PCBAInfo>();

        /// <summary>
        /// 資料庫讀取與寫入物件，創建時必須給定(主機路徑,登入帳號,登入密碼)
        /// </summary>
        QisdaTool.ProductInfoAccess Accsess = new QisdaTool.ProductInfoAccess("QTYSMARTSQL01.benq.corp.com\\QTYSF", "Qisdard", "Qisdard");

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            string ErrorMessage = "";

            if (e.KeyChar == 13)
            {
                ///將機台TRID輸入，創建一個物件
                NowProductInfo = new QisdaTool.ProductInfo(textBox1.Text);

                ///資料庫連線檢查
                if (Accsess.DataBaseConnectCheck(out ErrorMessage) == false)
                {
                    MessageBox.Show(ErrorMessage, "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                ///抓取機台產品訊息(將剛刷入的TRID進資料庫抓取相對應的機台資訊(包含ModelName,料號,工廠流線ID號碼))
                if (Accsess.CheckTRID(textBox1.Text, ref NowProductInfo, out ErrorMessage) == true)
                {
                    lab_Model.Text = NowProductInfo.ModelName;///Model Name
                    lab_PN.Text = NowProductInfo.PartNo;///料號
                    lab_ID.Text = NowProductInfo.ID;///工廠流線ID號碼
                    lab_TRID.Text = textBox1.Text.ToUpper().Trim();///TRID號碼
                }
                else
                {
                    MessageBox.Show(ErrorMessage, "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }


                ///資料上傳範例如下
                ///
                //if (Accsess.InsertTestResultRecord(NowProductInfo, "ASMDL", "FX3DL", "PASS", "PASS", "0.0.1", "0.1.0", "1.003", "20160122", "191030", out ErrorMessage) != true)
                //{
                //    ///上傳資料失敗
                //    MessageBox.Show(ErrorMessage, "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                //    return;
                //}


                ///取PCBA ID範例如下
                ///
                if (Accsess.GetPCBAIDandSN(textBox1.Text, ref ApolloPCBAInfo, Application.StartupPath + "\\QisdaToolPara.ini", out ErrorMessage) == false)
                {
                    MessageBox.Show(ErrorMessage, "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }


                ///上傳過站資訊 當站全部測項都完成後 判斷此站別是PASS or Fail
                ///
                ///NG==>QisdaTool.StationTestResult.NG
                if (Accsess.InsertStationShopfloorData(textBox1.Text, "ASML", QisdaTool.StationTestResult.NG, Application.StartupPath + "\\QisdaToolPara.ini", out ErrorMessage) == false)
                {
                    MessageBox.Show(ErrorMessage, "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }


                ///上傳過站資訊 當站全部測項都完成後 判斷此站別是PASS or Fail
                ///
                ///PASS ==>QisdaTool.StationTestResult.GOOD
                if (Accsess.InsertStationShopfloorData(textBox1.Text, "ASML", QisdaTool.StationTestResult.GOOD, Application.StartupPath + "\\QisdaToolPara.ini", out ErrorMessage) == false)
                {
                    MessageBox.Show(ErrorMessage, "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }





            }
        }

    }
}

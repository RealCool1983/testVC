using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Data;

namespace QisdaTool
{
    public class ProductInfo
    {
        public ProductInfo(string InputTRID)
        {
            ModelName = "";
            PartNo = "";
            SoNo = "";
            TRID = InputTRID;
            ID = "";
        }

        public string ModelName { get; set; }
        public string PartNo { get; set; }
        public string SoNo { get; set; }
        public string TRID { get; set; }
        public string ID { get; set; }
    }

    public class ProductInfoAccess
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="InputDbHost">主機名稱</param>
        /// <param name="InputDBUser">使用者名稱</param>
        /// <param name="InputDbPass">密碼</param>
        public ProductInfoAccess(string InputDbHost, string InputDBUser, string InputDbPass)
        {
            dbHost = InputDbHost;
            dbUser = InputDBUser;
            dbPass = InputDbPass;
            dbName = "WIP";
        }

        private string dbHost;
        private string dbUser;
        private string dbPass;
        private string dbName;

        public bool DataBaseConnectCheck(out string ErrorMessage)
        {
            ErrorMessage = "";
            bool CheckState = true;

            using (SqlConnection cn = new SqlConnection())
            {
                cn.ConnectionString = "server=" + dbHost + ";uid=" + dbUser + ";pwd=" + dbPass + ";database=" + dbName;
                try
                {
                    cn.Open();
                }
                catch (SqlException ex)
                {
                    ErrorMessage = ex.Message;
                    CheckState = false;
                    return (CheckState);
                }
            }
            return CheckState;
        }


        /// <summary>
        /// 檢查輸入的TRID號碼是否正確，並抓取此機台資訊
        /// </summary>
        /// <param name="TRID">輸入查詢的TRID號碼</param>
        /// <param name="NowProductInfo">查詢後的機台資訊將會存在此物件中</param>
        /// <param name="ErrorMessage">錯誤訊息</param>
        /// <returns></returns>
        public bool CheckTRID(string TRID, ref ProductInfo NowProductInfo, out string ErrorMessage)
        {
            ErrorMessage = "";
            bool CheckState = true;


            if (TRID.Length == 18 && (TRID.IndexOf("N") == 0 || TRID.IndexOf("R") == 0))
            {
                if (ProductInfoSearch(TRID, NowProductInfo, out ErrorMessage) != true)
                {
                    CheckState = false;
                }
            }
            else
            {
                CheckState = false;
                ErrorMessage = "TRID輸入錯誤";
            }

            return CheckState;
        }

        private bool ProductInfoSearch(string TRID, ProductInfo NowProductInfo, out string ErrorMessage)
        {
            //string dbHost = ResultReaderSystemPara.DataBaseHost;///資料庫位址
            //string dbUser = ResultReaderSystemPara.DataBaseAccontName;///資料庫使用者名稱
            //string dbPass = ResultReaderSystemPara.DataBaseAccontPassword;///"資料庫使用者密碼"
            //string dbName = "WIP";///資料庫名稱;

            bool CheckFlag = false;
            ErrorMessage = "";

            //InitializeProductInfo();

            using (SqlConnection cn = new SqlConnection())
            {
                cn.ConnectionString = "server=" + dbHost + ";uid=" + dbUser + ";pwd=" + dbPass + ";database=" + dbName;
                try
                {
                    cn.Open();
                }
                catch (SqlException ex)
                {
                    ErrorMessage = ex.ToString();
                    CheckFlag = false;
                    return (CheckFlag);
                }

                if (cn.State == ConnectionState.Open)
                {
                    SQL_PCBIDTable sql_PCBIDTable = new SQL_PCBIDTable();

                    string SelectColum = sql_PCBIDTable.SO + "," + sql_PCBIDTable.ID + "," + sql_PCBIDTable.Part_No + "," + sql_PCBIDTable.Model;

                    string sqlstr = "SELECT " + SelectColum + " From WIP.dbo.PCBID WHERE " + sql_PCBIDTable.TRID + " = " + "'" + TRID + "'";

                    SqlCommand cmd = new SqlCommand(sqlstr, cn);
                    SqlDataReader dr = cmd.ExecuteReader();

                    try
                    {
                        if (dr.Read() == true)
                        {
                            if (!dr.Equals(DBNull.Value))
                            {
                                NowProductInfo.SoNo = dr[sql_PCBIDTable.SO].ToString().Trim();
                                NowProductInfo.PartNo = dr[sql_PCBIDTable.Part_No].ToString().Trim();
                                NowProductInfo.ModelName = dr[sql_PCBIDTable.Model].ToString().Trim();
                                NowProductInfo.ID = dr[sql_PCBIDTable.ID].ToString().Trim();
                                NowProductInfo.TRID = TRID;
                                CheckFlag = true;
                            }
                        }
                        else
                        {
                            ErrorMessage = "查無此TRID : " + TRID + "資料!!!";
                            CheckFlag = false;
                        }
                    }
                    catch
                    {
                        ErrorMessage = "資料庫查詢錯誤!!!!(WIP.dbo.PCBID,TRID : " + TRID + ")";
                        CheckFlag = false;
                    }
                    finally
                    {
                        dr.Close();
                    }
                }
                else
                {
                    ErrorMessage = "資料庫連接錯誤!!!!(WIP.dbo.TRID)";
                    CheckFlag = false;
                }
            }
            return (CheckFlag);
        }


        /// <summary>
        /// 將檢測資料插入資料庫中
        /// </summary>
        /// <param name="NowProductInfo">當前機台資料物件</param>
        /// <param name="Station">當站站名</param>
        /// <param name="TestItem">測試項目</param>
        /// <param name="TestResult">測試結果 PASS,NG</param>
        /// <param name="MeasureValue">測試數值</param>
        /// <param name="NowDate">測試日期YYYYMMDD</param>
        /// <param name="NowTime">測試時間HHMMSS</param>
        /// <param name="ErrorMessage">錯誤訊息</param>
        /// <returns></returns>
        public bool InsertTestResultRecord(ProductInfo NowProductInfo, string Station, string TestItem, string TestResult, string MeasureValue, string NowDate, string NowTime, out string ErrorMessage)
        {
            //string dbHost = ResultReaderSystemPara.DataBaseHost;///資料庫位址
            //string dbUser = ResultReaderSystemPara.DataBaseAccontName;///資料庫使用者名稱
            //string dbPass = ResultReaderSystemPara.DataBaseAccontPassword;///"資料庫使用者密碼"
            //string dbName = "WIP";///資料庫名稱;
            ErrorMessage = "";
            using (SqlConnection cn = new SqlConnection())
            {
                cn.ConnectionString = "server=" + dbHost + ";uid=" + dbUser + ";pwd=" + dbPass + ";database=" + dbName;
                cn.Open();

                if (cn.State == ConnectionState.Open)
                {

                    string InsertToUsbTestRecord = "INSERT INTO PICS.dbo.HCS_UsbTestRecode(";
                    string VALUES = ") VALUES(";

                    SQL_HcsUsbTestRecordTable sql_TestRecord = new SQL_HcsUsbTestRecordTable();

                    SqlTransaction tran = cn.BeginTransaction();
                    try
                    {
                        string sqlstr = InsertToUsbTestRecord
                                        + sql_TestRecord.TRID + "," + sql_TestRecord.ID + ","
                                        + sql_TestRecord.PN + ","
                                        + sql_TestRecord.Model + ","
                                        + sql_TestRecord.Datein + "," + sql_TestRecord.Timein + ","
                                        + sql_TestRecord.TestItem + ","
                                        + sql_TestRecord.TestResult + ","
                                        + sql_TestRecord.SO + ","
                                        + sql_TestRecord.Station + ","
                                        + sql_TestRecord.MeasureValue

                                        + VALUES
                                        + "'" + NowProductInfo.TRID + "'" + "," + "'" + NowProductInfo.ID + "'" + ","
                                        + "'" + NowProductInfo.PartNo + "'" + ","
                                        + "'" + NowProductInfo.ModelName + "'" + ","
                                        + "'" + NowDate + "'" + "," + "'" + NowTime + "'" + ","
                                        + "'" + TestItem + "'" + ","
                                        + "'" + TestResult + "'" + ","
                                        + "'" + NowProductInfo.SoNo + "'" + ","
                                        + "'" + Station + "'" + ","
                                        + "'" + MeasureValue + "'"
                                        + ")";

                        SqlCommand cmd = new SqlCommand(sqlstr, cn, tran);

                        cmd.ExecuteNonQuery();
                        tran.Commit();

                        return (true);
                    }
                    catch (SqlException ex)
                    {
                        tran.Rollback();
                        ErrorMessage = ex.ToString();
                        return (false);
                    }
                }
                else
                {
                    return (false);
                }
            }
        }


        #region HcsUsbTestRecordTable
        private class SQL_HcsUsbTestRecordTable
        {
            public SQL_HcsUsbTestRecordTable()
            {
                TRID = "TRID";
                ID = "ID";
                PN = "PN";
                Model = "Model";
                Station = "Station";
                TestItem = "TestItem";
                TestResult = "TestResult";
                Datein = "Datein";
                Timein = "Timein";
                SO = "SO";
                TableName = "TableName";
                DockName = "DockName";
                MeasureValue = "MeasureValue";

            }

            public string TRID { get; set; }
            public string ID { get; set; }
            public string PN { get; set; }
            public string Model { get; set; }
            public string Station { get; set; }
            public string TestItem { get; set; }
            public string TestResult { get; set; }
            public string Datein { get; set; }
            public string Timein { get; set; }
            public string SO { get; set; }
            public string TableName { get; set; }
            public string DockName { get; set; }
            public string MeasureValue { get; set; }
        }
        #endregion

        #region PCBIDTable
        private class SQL_PCBIDTable
        {
            public SQL_PCBIDTable()
            {
                Part_No = "Part_No";
                SO = "SO";
                Model = "Model";
                TRID = "TRID";
                ID = "ID";
            }

            public string ID { get; set; }
            public string TRID { get; set; }
            public string SO { get; set; }
            public string Model { get; set; }
            public string Part_No { get; set; }

        }
        #endregion

        #region SSCTable
        private class SQL_SSCTable
        {
            public SQL_SSCTable()
            {
                SoNo = "SoNo";
                PN = "PN";
                SoQty = "SoQty";
                Model = "Model";
                CRT = "CRT";
                Fac = "Fac";
            }

            public string SoNo { get; set; }
            public string PN { get; set; }
            public string SoQty { get; set; }
            public string Model { get; set; }
            public string CRT { get; set; }
            public string Fac { get; set; }
        }
        #endregion
    }





}

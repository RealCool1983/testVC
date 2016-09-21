using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Data;
using System.Runtime.InteropServices;
using System.IO;


namespace QisdaTool
{
    public enum StationTestResult
    {
        GOOD = 0,
        NG =1
    }


    public class ProductInfo
    {
        public ProductInfo(string InputTRID)
        {
            ModelName = "";
            PartNo = "";
            SoNo = "";
            TRID = InputTRID;
            ID = "";
            Routecode = "";
        }

        public string ModelName { get; set; }
        public string PartNo { get; set; }
        public string SoNo { get; set; }
        public string TRID { get; set; }
        public string ID { get; set; }
        public string Routecode { get; set; }
    }

    public class PCBAInfo
    {
        public PCBAInfo()
        {
            KeypartType = "";
            KeypartSn = "";
            TestItem = "";
            MeasureValue = "";
        }

        public string KeypartType { get; set; }
        public string KeypartSn { get; set; }
        public string TestItem { get; set; }
        public string MeasureValue { get; set; }
    }


    public class ProductInfoAccess
    {

        public class SetupIni
        {

            public string path;
            [DllImport("kernel32", CharSet = CharSet.Unicode)]
            private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
            [DllImport("kernel32", CharSet = CharSet.Unicode)]
            private static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);

            public void IniWriteValue(string Section, string Key, string Value, string inipath)
            {
                WritePrivateProfileString(Section, Key, Value, inipath);
            }
            public string IniReadValue(string Section, string Key, string inipath)
            {
                StringBuilder temp = new StringBuilder(255);
                int i = GetPrivateProfileString(Section, Key, "", temp, 255, inipath);
                return temp.ToString();
            }
        }

        private class FindPCBAInfo
        {
            public FindPCBAInfo()
            {
                MainAssy = "";
                SubAssy = "";
            }

            public string MainAssy;
            public string SubAssy;
        }

        private class Timecode
        {
            public Timecode()
            {
                TPCODE = "";
                SHIFTCODE = "";
                SHIFTTYPECODE = "";
                NowTime = "";
                NowDate = "";
            }

            public string TPCODE{ get; set; }
            public string SHIFTCODE { get; set; }
            public string SHIFTTYPECODE{ get; set; }
            public string NowTime { get; set; }
            public string NowDate { get; set; }
        }

        SetupIni Ini = new SetupIni();

        List<FindPCBAInfo> FindInfoList = new List<FindPCBAInfo>();

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

        /// <summary>
        /// 資料庫連線檢查Function
        /// </summary>
        /// <param name="ErrorMessage">錯誤訊息</param>
        /// <returns>True 表示資料庫連線正常，False表資料庫連線異常</returns>
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
            bool CheckFlag = false;
            ErrorMessage = "";

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
        public bool InsertTestResultRecord(ProductInfo NowProductInfo, string Station, string TestItem, string TestResult, string MeasureValue,
                string HwVersion, string SwVersion, string ToolVersion,
                string NowDate, string NowTime, out string ErrorMessage)
        {
            ErrorMessage = "";


                ///抓取機台產品訊息(將剛刷入的TRID進資料庫抓取相對應的機台資訊(包含ModelName,料號,工廠流線ID號碼))
            CheckTRID(NowProductInfo.TRID, ref NowProductInfo, out ErrorMessage);

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
                    return (false);
                }

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
                                        + sql_TestRecord.MeasureValue + ","
                                        + sql_TestRecord.HwVersion + ","
                                        + sql_TestRecord.SwVersion + ","
                                        + sql_TestRecord.ToolVersion

                                        + VALUES
                                        + "'" + NowProductInfo.TRID + "'" + "," + "'" + NowProductInfo.ID + "'" + ","
                                        + "'" + NowProductInfo.PartNo + "'" + ","
                                        + "'" + NowProductInfo.ModelName + "'" + ","
                                        + "'" + NowDate + "'" + "," + "'" + NowTime + "'" + ","
                                        + "'" + TestItem + "'" + ","
                                        + "'" + TestResult + "'" + ","
                                        + "'" + NowProductInfo.SoNo + "'" + ","
                                        + "'" + Station + "'" + ","
                                        + "'" + MeasureValue + "'" + ","
                                        + "'" + HwVersion + "'" + ","
                                        + "'" + SwVersion + "'" + ","
                                        + "'" + ToolVersion + "'"
                                        + ")";

                        SqlCommand cmd = new SqlCommand(sqlstr, cn, tran);

                        cmd.ExecuteNonQuery();
                        tran.Commit();

                        return (true);
                    }
                    catch (SqlException ex)
                    {
                        tran.Rollback();
                        ErrorMessage = ex.Message;
                        return (false);
                    }
                }
                else
                {
                    return (false);
                }
            }
        }


        public bool GetPCBAIDandSN(string ApolloTRID, ref List<PCBAInfo> PCBAInfoList, string ApplicationPath, out string ErrorMessage)
        {
            bool CheckFlag = true;
            ErrorMessage = "";
            PCBAInfoList.Clear();
            FindInfoList.Clear();

            string SQL = "";
            string ReadFindInfo = "";


            ProductInfo tmpParoduct = new ProductInfo(ApolloTRID);
            if (CheckTRID(ApolloTRID, ref tmpParoduct, out ErrorMessage) == false)
            {
                ErrorMessage = ErrorMessage + "\n 故無法取得PCBA資料!!!";
                return false;
            }

            if (File.Exists(ApplicationPath) == false)
            {
                ErrorMessage = "外部檔不存在!!!\n路徑 : " + ApplicationPath;
                CheckFlag = false;
                return (CheckFlag);
            }

            ReadFindInfo = Ini.IniReadValue("BoardIDGet", tmpParoduct.PartNo.ToUpper(), ApplicationPath);

            if (ReadFindInfo == "")
            {
                ErrorMessage = "外部檔 : " + ApplicationPath + "\n Section: [BoardIDGet]  \n Key : " + tmpParoduct.PartNo.ToUpper() + "\n 內容為空!!!";
                CheckFlag = false;
                return (CheckFlag);
            }

            string[] tmpSplit = new string[] { "," };
            string[] tmp = ReadFindInfo.Split(tmpSplit, StringSplitOptions.RemoveEmptyEntries);

            string[] SubtmpSplit = new string[] { "#" };

            //將外部檔設定解碼看物件需要搜索幾層
            for (int i = 0; i < tmp.Count(); i++)
            {
                string[] Subtmp = tmp[i].Split(SubtmpSplit, StringSplitOptions.RemoveEmptyEntries);

                FindPCBAInfo tmpFindInfo = new FindPCBAInfo();

                if (Subtmp.Count() == 2)
                {
                    tmpFindInfo.MainAssy = Subtmp[0];
                    tmpFindInfo.SubAssy = Subtmp[1];

                    FindInfoList.Add(tmpFindInfo);

                    PCBAInfo tmpPCBAInfo = new PCBAInfo();

                    if (GetMainAssySubAssyPCBInfo(ApolloTRID, tmpFindInfo.MainAssy, tmpFindInfo.SubAssy, out tmpPCBAInfo, out ErrorMessage) == false)
                    {
                        CheckFlag = false;
                        return (CheckFlag);
                    }
                    PCBAInfoList.Add(tmpPCBAInfo);
                }
                else
                {
                    tmpFindInfo.MainAssy = Subtmp[0];
                    tmpFindInfo.SubAssy = "";
                    FindInfoList.Add(tmpFindInfo);

                    PCBAInfo tmpPCBAInfo = new PCBAInfo();

                    if (GetMainAssyPCBAInfo(ApolloTRID, tmpFindInfo.MainAssy, out tmpPCBAInfo, out ErrorMessage) == false)
                    {
                        CheckFlag = false;
                        return (CheckFlag);
                    }

                    PCBAInfoList.Add(tmpPCBAInfo);
                }
            }

            GC.Collect();
            return (CheckFlag);

        }

        private bool GetEngineTRID(string ApolloTRID, string MainAssyType, out string EngineTRID, out string ErrorMessage)
        {
            bool CheckFlag = true;
            ErrorMessage = "";
            EngineTRID = "";


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
                    CheckFlag = false;
                    return (CheckFlag);
                }

                if (cn.State == ConnectionState.Open)
                {
                    string SQL = "select * from openquery(qtymes,'select * from ( ";
                    SQL = SQL + "select M.Rcard ApolloTRID,M.MCARD EngineSN,S.RCARD EngineTRID,M.EATTRIBUTE1 KeyPartType from tblonwipitem M ";
                    SQL = SQL + "join tblonwipitem S on M.Mcard = S.Mcard ";
                    SQL = SQL + "where M.Rcard=''" + ApolloTRID.Trim() + "''";
                    SQL = SQL + "and M.EATTRIBUTE1=''" + MainAssyType.Trim() + "'' ";
                    SQL = SQL + "and S.RCARD !=''" + ApolloTRID.Trim() + "''";
                    SQL = SQL + "order by M.mdate desc,M.Mtime desc)where rownum=''1''')";


                    SqlCommand cmd = new SqlCommand(SQL, cn);

                    Console.WriteLine(cmd.CommandText);

                    SqlDataReader dr = cmd.ExecuteReader();
                    try
                    {
                        if (dr.Read() == true)
                        {
                            if (!dr.Equals(DBNull.Value))
                            {
                                EngineTRID = dr["EngineTRID"].ToString().Trim();
                                CheckFlag = true;
                            }
                        }
                        else
                        {
                            ErrorMessage = "查無此TRID : " + ApolloTRID + "資料!!!\n" + "KeyPartType : " + MainAssyType + "資料!!!";
                            CheckFlag = false;
                        }
                    }
                    catch
                    {
                        ErrorMessage = "資料庫查詢錯誤!!!! \n SQL : " + SQL;
                        CheckFlag = false;
                    }
                    finally
                    {
                        dr.Close();
                    }
                }
                else
                {
                    ErrorMessage = "資料庫連接錯誤!!!!(GetEngineTRID)";
                    CheckFlag = false;
                }
            }


            return CheckFlag;

        }

        private bool GetMainAssySubAssyPCBInfo(string TRID, string MainAssyType,string SubAssy, out PCBAInfo tmpPCBAInfo, out string ErrorMessage)
        {
            bool CheckFlag = true;
            string ApolloEngineTRID = "";

            ErrorMessage = "";
            tmpPCBAInfo = new PCBAInfo();


            if (GetEngineTRID(TRID, MainAssyType, out ApolloEngineTRID, out ErrorMessage) == false)
            {
                CheckFlag = false;
                return CheckFlag;
            }

            if(GetMainAssyPCBAInfo(ApolloEngineTRID, SubAssy, out tmpPCBAInfo, out ErrorMessage) == false)
            {
                CheckFlag = false;
                return CheckFlag;
            }

            return CheckFlag;

        }

        private bool GetMainAssyPCBAInfo(string TRID, string MainAssyType, out PCBAInfo tmpPCBAInfo, out string ErrorMessage)
        {

            bool CheckFlag = true;
            ErrorMessage = "";
            tmpPCBAInfo = new PCBAInfo();

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
                    CheckFlag = false;
                    return (CheckFlag);
                }

                if (cn.State == ConnectionState.Open)
                {
                    string SQL = "select top 1  M.RCARD TRID,M.EATTRIBUTE1 KeyPartType,M.MCARD KeyPartSn,U.Testitem TestItem,U.Measurevalue MeasureValue,U.datein Date,U.timein Time ";
                    SQL = SQL + "from  pics.dbo.HCS_UsbTestRecode U join pics.dbo.keymapping K on K.Mainkey = U.Testitem ";
                    SQL = SQL + "join(select * from openquery(qtymes,'";
                    SQL = SQL + "select * from (";
                    SQL = SQL + "select RCARD,MCARD,EATTRIBUTE1 from tblonwipitem ";
                    SQL = SQL + "where RCARD=''" + TRID + "'' and EATTRIBUTE1=''" + MainAssyType + "''";
                    SQL = SQL + "order by mdate desc,mtime desc) where rownum=''1''')";
                    SQL = SQL + ")M on K.Mappingkey = M.EATTRIBUTE1 ";
                    SQL = SQL + "where U.trid ='" + TRID + "' and M.EATTRIBUTE1 = '" + MainAssyType + "'";
                    SQL = SQL + "order by U.datein desc,U.timein desc";

                    SqlCommand cmd = new SqlCommand(SQL, cn);
                    //cmd.Parameters.AddWithValue("@TRID", TRID);
                    //cmd.Parameters.AddWithValue("@MainAssyType", MainAssyType);

                    Console.WriteLine(cmd.CommandText);

                    SqlDataReader dr = cmd.ExecuteReader();
                    try
                    {
                        if (dr.Read() == true)
                        {
                            if (!dr.Equals(DBNull.Value))
                            {
                                tmpPCBAInfo.KeypartType = dr["KeyPartType"].ToString().Trim();
                                tmpPCBAInfo.KeypartSn = dr["KeyPartSn"].ToString().Trim();
                                tmpPCBAInfo.TestItem = dr["TestItem"].ToString().Trim();
                                tmpPCBAInfo.MeasureValue = dr["MeasureValue"].ToString().Trim();
                                CheckFlag = true;
                            }
                        }
                        else
                        {
                            tmpPCBAInfo.KeypartType = MainAssyType;


                            ErrorMessage = "查無此TRID : " + TRID + "資料!!!\n" + "KeyPartType : " + MainAssyType + "資料!!! \n 缺少對應資料(pics.dbo.keymapping)";
                            CheckFlag = false;
                        }
                    }
                    catch
                    {
                        ErrorMessage = "資料庫查詢錯誤!!!! \n SQL : " + SQL;
                        CheckFlag = false;
                    }
                    finally
                    {
                        dr.Close();
                    }
                }
                else
                {
                    ErrorMessage = "資料庫連接錯誤!!!!(GetMainAssyPCBAInfo)";
                    CheckFlag = false;
                }
            }
            return (CheckFlag);
        }

        //----------------------------------------------------------------------------------------------
        private bool GetRoute(ProductInfo NowProductInfo, out string ErrorMessage)
        {
            bool CheckFlag = false;
            ErrorMessage = "";

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
                    CheckFlag = false;
                    return (CheckFlag);
                }


                if (cn.State == ConnectionState.Open)
                {
                    SQL_TBLITEM2ROUTE sql_Tblitem2routeTable = new SQL_TBLITEM2ROUTE();

                    string SelectColum = sql_Tblitem2routeTable.ROUTECODE;

                    string sqlstr = "SELECT top 1 " + SelectColum + " From Shopfloor.dbo.tblitem2route WHERE " + sql_Tblitem2routeTable.ITEMCODE + " =  @PartNo order by MDATE desc,MTIME desc";

                    SqlCommand cmd = new SqlCommand(sqlstr, cn);
                    cmd.Parameters.AddWithValue("@PartNo", NowProductInfo.PartNo);

                    SqlDataReader dr = cmd.ExecuteReader();
                    try
                    {
                        if (dr.Read() == true)
                        {
                            if (!dr.Equals(DBNull.Value))
                            {
                                NowProductInfo.Routecode = dr[sql_Tblitem2routeTable.ROUTECODE].ToString().Trim();
                                CheckFlag = true;
                            }
                        }
                        else
                        {
                            ErrorMessage = "查無此PN : " + NowProductInfo.PartNo + " RouteCode資料!!!";
                            CheckFlag = false;
                        }
                    }
                    catch
                    {
                        ErrorMessage = "資料庫查詢錯誤!!!!(Shopfloor.dbo.tblitem2route : " + NowProductInfo.PartNo + ")";
                        CheckFlag = false;
                    }
                    finally
                    {
                        dr.Close();
                    }
                }
                else
                {
                    ErrorMessage = "資料庫連接錯誤!!!!(Shopfloor.dbo.tblitem2route)";
                    CheckFlag = false;
                }
            }
            return (CheckFlag);
        }

        private bool GetTimeCode(ref Timecode tmpTimcode,out string ErrorMessage)
        {
            bool CheckFlag = false;
            ErrorMessage = "";

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
                    CheckFlag = false;
                    return (CheckFlag);
                }

                if (cn.State == ConnectionState.Open)
                {
                    string NowDate = DateTime.Now.ToString("yyyyMMdd");
                    string NowTime = DateTime.Now.ToString("HHmmss");

                    if (int.Parse(NowTime) >= 73000 && int.Parse(NowTime) < 80001)
                    {
                        NowTime = "80001";
                    }


                    string sqlstr = "select TPCODE,SHIFTCODE,SHIFTTYPECODE from ShopFloor.dbo.TBLTP where @NowTime >=TPBTIME and @NowTime <=TPETIME ";

                    SqlCommand cmd = new SqlCommand(sqlstr, cn);
                    cmd.Parameters.AddWithValue("@NowTime", NowTime);

                    SqlDataReader dr = cmd.ExecuteReader();
                    try
                    {
                        if (dr.Read() == true)
                        {
                            if (!dr.Equals(DBNull.Value))
                            {
                                tmpTimcode.NowDate = NowDate;
                                tmpTimcode.NowTime = NowTime;
                                tmpTimcode.SHIFTCODE = dr["SHIFTCODE"].ToString().Trim();
                                tmpTimcode.TPCODE = dr["TPCODE"].ToString().Trim();
                                tmpTimcode.SHIFTTYPECODE = dr["SHIFTTYPECODE"].ToString().Trim();

                                CheckFlag = true;
                            }
                        }
                        else
                        {
                            ErrorMessage = "查無此時段 : " + NowTime + " TPCODE資料!!!";
                            CheckFlag = false;
                        }
                    }
                    catch
                    {
                        ErrorMessage = "資料庫查詢錯誤!!!!(ShopFloor.dbo.TBLTP : 當前時段 " + NowTime + ")";
                        CheckFlag = false;
                    }
                    finally
                    {
                        dr.Close();
                    }
                }
                else
                {
                    ErrorMessage = "資料庫連接錯誤!!!!(ShopFloor.dbo.TBLTP)";
                    CheckFlag = false;
                }
            }
            return (CheckFlag);
        }

        public bool InsertStationShopfloorData(string ApolloTRID, string StationName, StationTestResult StationResult, string ApplicationPath, out string ErrorMessage)
        {
            bool CheckFlag = true;
            ErrorMessage = "";

            string MOCODE="";
            string RCARD="";
            string RCARDSEQ="";
            string TCARD="";
            string MODELCODE="";
            string ITEMCODE="";
            string ROUTECODE ="";
            string OPCODE ="";
            string SEGCODE="";
            string SSCODE ="";
            string RESCODE ="";
            string SHIFTTYPECODE="";
            string SHIFTCODE ="";
            string TPCODE ="";
            string SHIFTDAY="";
            string ECODE="";
            string ACTION ="";
            string ACTIONRESULT ="";
            string CARTONCODE ="";
            string PALLETCODE="";
            string MUSER="";
            string MDATE="";
            string MTIME ="";
            string FLAG ="";
            string EMESSAGE ="";
            string EATTRIBUTE1="";


            ProductInfo tmpParoduct = new ProductInfo(ApolloTRID);
            Timecode tmpTimeCode = new Timecode();


            if (CheckTRID(ApolloTRID, ref tmpParoduct, out ErrorMessage) == false)
            {
               ErrorMessage = ErrorMessage + "\n 故無法插入過站資料至MES資料庫!!!";
               return false;
            }

            if (GetRoute(tmpParoduct, out ErrorMessage) == false)
            {
                ErrorMessage = ErrorMessage + "\n 故無法插入過站資料至MES資料庫!!!";
                return false;
            }

            if (GetTimeCode(ref tmpTimeCode, out ErrorMessage) == false)
            {
                ErrorMessage = ErrorMessage + "\n 故無法插入過站資料至MES資料庫!!!";
                return false;
            }

            if (File.Exists(ApplicationPath) == false)
            {
                ErrorMessage = "外部檔不存在!!!\n路徑 : " + ApplicationPath;
                return (false);
            }

            string tmpLineName = Ini.IniReadValue("MesLineCode", "LineName", ApplicationPath);

            if (tmpLineName == "")
            {
                ErrorMessage = "外部檔 : " + ApplicationPath + "\n Section: [MesLineCode]  \n Key : LineName \n 內容為空!!!";
                return (false);
            }

            string tmpSegment = SelectTableValue("PICS.dbo.picslne", "Segment", "MESLINE", tmpLineName, out ErrorMessage);

            MOCODE = tmpParoduct.SoNo.Substring(tmpParoduct.SoNo.Length-6);
            RCARD = tmpParoduct.TRID;
            RCARDSEQ = "0";
            TCARD = "";
            MODELCODE = tmpParoduct.ModelName;
            ITEMCODE = tmpParoduct.PartNo;
            ROUTECODE = tmpParoduct.Routecode;
            OPCODE = StationName.ToUpper();
            SEGCODE = tmpSegment;
            SSCODE = tmpLineName;
            RESCODE = SSCODE + "-" + OPCODE;
            SHIFTTYPECODE = tmpTimeCode.SHIFTTYPECODE;
            SHIFTCODE = tmpTimeCode.SHIFTCODE;
            TPCODE = tmpTimeCode.TPCODE;
            SHIFTDAY = tmpTimeCode.NowDate;

            switch ((int)StationResult)
            {
                case (int)StationTestResult.GOOD:
                    ECODE = "";
                    ACTION = "GOOD";
                    ACTIONRESULT = "GOOD";
                    break;

                case (int)StationTestResult.NG:
                    ECODE = StationName.ToUpper().Trim();
                    ACTION = "NG";
                    ACTIONRESULT = "NG";
                    break;
            }

            CARTONCODE = "";
            PALLETCODE = "";
            MUSER = "AUTO";
            MDATE = tmpTimeCode.NowDate;
            MTIME = tmpTimeCode.NowTime;
            FLAG = "Q";
            EMESSAGE = "";
            EATTRIBUTE1 = "";

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
                    return (false);
                }

                if (cn.State == ConnectionState.Open)
                {

                    string InsertToTBLERPONWIP = "INSERT INTO ShopFloor.dbo.TBLERPONWIP(";
                    string VALUES = ") VALUES(";

                    SQL_TBLIERPONWIP sql_TBLERPONWIP = new SQL_TBLIERPONWIP();

                    SqlTransaction tran = cn.BeginTransaction();
                    try
                    {
                        string sqlstr = InsertToTBLERPONWIP
                                        + sql_TBLERPONWIP.MOCODE+ "," + sql_TBLERPONWIP.RCARD + ","
                                        + sql_TBLERPONWIP.RCARDSEQ + ","
                                        + sql_TBLERPONWIP.TCARD + ","
                                        + sql_TBLERPONWIP.MODELCODE + "," + sql_TBLERPONWIP.ITEMCODE + ","
                                        + sql_TBLERPONWIP.ROUTECODE + ","
                                        + sql_TBLERPONWIP.OPCODE + ","
                                        + sql_TBLERPONWIP.SEGCODE + ","
                                        + sql_TBLERPONWIP.SSCODE + ","
                                        + sql_TBLERPONWIP.RESCODE + ","
                                        + sql_TBLERPONWIP.SHIFTTYPECODE + ","
                                        + sql_TBLERPONWIP.SHIFTCODE + ","
                                        + sql_TBLERPONWIP.TPCODE + ","
                                        + sql_TBLERPONWIP.SHIFTDAY + ","
                                        + sql_TBLERPONWIP.ECODE + ","
                                        + sql_TBLERPONWIP.ACTION + ","
                                        + sql_TBLERPONWIP.ACTIONRESULT + ","
                                        + sql_TBLERPONWIP.CARTONCODE + ","
                                        + sql_TBLERPONWIP.PALLETCODE + ","
                                        + sql_TBLERPONWIP.MUSER + ","
                                        + sql_TBLERPONWIP.MDATE + ","
                                        + sql_TBLERPONWIP.MTIME + ","
                                        + sql_TBLERPONWIP.FLAG + ","
                                        + sql_TBLERPONWIP.EMESSAGE + ","
                                        + sql_TBLERPONWIP.EATTRIBUTE1 

                                        + VALUES
                                        + "'" + MOCODE + "'" + "," + "'" + RCARD + "'" + ","
                                        + "'" + RCARDSEQ + "'" + ","
                                        + "'" + TCARD + "'" + ","
                                        + "'" + MODELCODE + "'" + "," + "'" + ITEMCODE + "'" + ","
                                        + "'" + ROUTECODE + "'" + ","
                                        + "'" + OPCODE + "'" + ","
                                        + "'" + SEGCODE + "'" + ","
                                        + "'" + SSCODE + "'" + ","
                                        + "'" + RESCODE + "'" + ","
                                        + "'" + SHIFTTYPECODE + "'" + ","
                                        + "'" + SHIFTCODE + "'" + ","
                                        + "'" + TPCODE + "'" + ","
                                        + "'" + SHIFTDAY + "'" + ","
                                        + "'" + ECODE + "'" + ","
                                        + "'" + ACTION + "'" + ","
                                        + "'" + ACTIONRESULT + "'" + ","
                                        + "'" + CARTONCODE + "'" + ","
                                        + "'" + PALLETCODE + "'" + ","
                                        + "'" + MUSER + "'" + ","
                                        + "'" + MDATE + "'" + ","
                                        + "'" + MTIME + "'" + ","
                                        + "'" + FLAG + "'" + ","
                                        + "'" + EMESSAGE + "'" + ","
                                        + "'" + EATTRIBUTE1 + "'"
                                        + ")";

                        SqlCommand cmd = new SqlCommand(sqlstr, cn, tran);

                        cmd.ExecuteNonQuery();
                        tran.Commit();

                        return (true);
                    }
                    catch (SqlException ex)
                    {
                        tran.Rollback();
                        ErrorMessage = ex.Message;
                        return (false);
                    }
                }
                else
                {
                    return (false);
                }
            }

        }

        public string SelectTableValue(string TableName, string TargetColumName, string ColumName, string Value, out string ErrorMessage)
        {

            string tmpResult = "";
            ErrorMessage = "";

            using (SqlConnection cn = new SqlConnection())
            {
                cn.ConnectionString = "server=" + dbHost + ";uid=" + dbUser + ";pwd=" + dbPass + ";database=" + dbName;
                cn.Open();

                if (cn.State == ConnectionState.Open)
                {
                    //MessageBox.Show("連接成功");

                    string SELECT_Table = @"SELECT " + TargetColumName + " FROM " + TableName + " WHERE "
                                                                + ColumName + "=" + "'" + Value + "'";
                    try
                    {
                        SqlCommand cmd = new SqlCommand(SELECT_Table, cn);
                        SqlDataReader dr = cmd.ExecuteReader();

                        if (dr.Read() == true && !dr.Equals(DBNull.Value))
                        {

                            tmpResult = dr[TargetColumName].ToString();

                        }
                    }
                    catch (SqlException ex)
                    {

                    }
                }
                else
                {

                }
            }

            return tmpResult;
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
                HwVersion = "HwVersion";
                SwVersion = "SwVersion";
                ToolVersion = "ToolVersion";
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
            public string HwVersion { get; set; }
            public string SwVersion { get; set; }
            public string ToolVersion { get; set; }
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

        #region tblitem2route
        private class SQL_TBLITEM2ROUTE
        {
            public SQL_TBLITEM2ROUTE()
            {
                ITEMCODE = "ITEMCODE";
                ROUTECODE = "ROUTECODE";
                MDATE = "MDATE";
                MTIME = "MTIME";
            }
            public string ITEMCODE { get; set; }
            public string ROUTECODE { get; set; }
            public string MDATE { get; set; }
            public string MTIME { get; set; }
        }
        #endregion


        #region tblerponwip
        private class SQL_TBLIERPONWIP
        {
            public SQL_TBLIERPONWIP()
            {
                MOCODE = "MOCODE";
                RCARD = "RCARD";
                RCARDSEQ = "RCARDSEQ";
                TCARD = "TCARD";
                MODELCODE = "MODELCODE";
                ITEMCODE = "ITEMCODE";
                ROUTECODE = "ROUTECODE";
                OPCODE = "OPCODE";
                SEGCODE = "SEGCODE";
                SSCODE = "SSCODE";
                RESCODE = "RESCODE";
                SHIFTTYPECODE = "SHIFTTYPECODE";
                SHIFTCODE = "SHIFTCODE";
                TPCODE = "TPCODE";
                SHIFTDAY = "SHIFTDAY";
                ECODE = "ECODE";
                ACTION = "ACTION";
                ACTIONRESULT = "ACTIONRESULT";
                CARTONCODE = "CARTONCODE";
                PALLETCODE = "PALLETCODE";
                MUSER = "MUSER";
                MDATE = "MDATE";
                MTIME = "MTIME";
                FLAG = "FLAG";
                EMESSAGE = "EMESSAGE";
                EATTRIBUTE1 = "EATTRIBUTE1";
            }
            public string MOCODE { get; set; }
            public string RCARD { get; set; }
            public string RCARDSEQ { get; set; }
            public string TCARD { get; set; }
            public string MODELCODE { get; set; }
            public string ITEMCODE { get; set; }
            public string ROUTECODE { get; set; }
            public string OPCODE { get; set; }
            public string SEGCODE { get; set; }
            public string SSCODE { get; set; }
            public string RESCODE { get; set; }
            public string SHIFTTYPECODE { get; set; }
            public string SHIFTCODE { get; set; }
            public string TPCODE { get; set; }
            public string SHIFTDAY { get; set; }
            public string ECODE { get; set; }
            public string ACTION { get; set; }
            public string ACTIONRESULT { get; set; }
            public string CARTONCODE { get; set; }
            public string PALLETCODE { get; set; }
            public string MUSER { get; set; }
            public string MDATE { get; set; }
            public string MTIME { get; set; }
            public string FLAG { get; set; }
            public string EMESSAGE { get; set; }
            public string EATTRIBUTE1 { get; set; }
        }
        #endregion

    }

}

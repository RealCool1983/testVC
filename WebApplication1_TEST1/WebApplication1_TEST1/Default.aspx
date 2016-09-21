<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebApplication1_TEST1._Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    <style type="text/css">
        .style1
        {
            width: 150px;
        }
        .style2
        {
            width: 382px;
        }
        .style3
        {
            width: 150px;
            height: 26px;
        }
        .style4
        {
            width: 382px;
            height: 26px;
        }
        .style5
        {
            height: 26px;
        }
        .style6
        {
            width: 150px;
            height: 10px;
        }
        .style7
        {
            width: 382px;
            height: 10px;
        }
        .style8
        {
            height: 10px;
        }
        .style9
        {
            width: 374px;
        }
        .style10
        {
            width: 63px;
        }
        .style12
        {
            width: 374px;
            height: 22px;
        }
        .style13
        {
            width: 63px;
            height: 22px;
        }
        .style14
        {
            background-color: #999966;
        }
        .style15
        {
            width: 382px;
            background-color: #999966;
        }
        .style16
        {
            width: 150px;
            background-color: #999966;
        }
        .style17
        {
            width: 382px;
            background-color: #CCFF99;
        }
        .style18
        {
            width: 150px;
            background-color: #CCFF99;
        }
        </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        HI! HAVE NICE DAY</div>
    <p>
        &nbsp;</p>
    <table style="width: 100%; height: 106px;">
        <tr>
            <td class="style6" bgcolor="#99CCFF">
                &nbsp;</td>
            <td class="style7" bgcolor="#99CCFF">
                <asp:Label ID="MSG" runat="server" Text="---"></asp:Label>
            </td>
            <td class="style8" bgcolor="#99CCFF">
                <asp:Label ID="MSG0" runat="server" Text="MD5 HEX"></asp:Label>
            </td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                Carrier ID</td>
            <td class="style2" bgcolor="#99CCFF">
        <asp:TextBox ID="input" runat="server" Width="225px" ></asp:TextBox>
            </td>
            <td bgcolor="#99CCFF">
                <asp:Label ID="SOMKEY" runat="server" Text="---"></asp:Label>
            </td>
        </tr>
        <tr>
            <td class="style3" bgcolor="#99CCFF">
                FPGA_A</td>
            <td class="style4" bgcolor="#99CCFF">
        <asp:TextBox ID="input0" runat="server" Width="225px" ></asp:TextBox>
            </td>
            <td class="style5" bgcolor="#99CCFF">
                <asp:Label ID="ABOKEY" runat="server" Text="---"></asp:Label>
            </td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                FPGA_B</td>
            <td class="style2" bgcolor="#99CCFF">
        <asp:TextBox ID="input1" runat="server" Width="225px" ></asp:TextBox>
            </td>
            <td bgcolor="#99CCFF">
                <asp:Label ID="BBOKEY" runat="server" Text="---"></asp:Label>
            </td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                Wifi Mac</td>
            <td class="style2" bgcolor="#99CCFF">
        <asp:TextBox ID="input2" runat="server" Width="225px" ></asp:TextBox>
            </td>
            <td bgcolor="#99CCFF">
                <asp:Label ID="WIFIKEY" runat="server" Text="---"></asp:Label>
            </td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                Input</td>
            <td class="style2" bgcolor="#99CCFF">
                <asp:Label ID="Label2" runat="server" Text="---"></asp:Label>
            </td>
            <td bgcolor="#99CCFF">
                &nbsp;</td>
        </tr>
        <tr>
            <td class="style18">
                AES
                KEY</td>
            <td class="style17">
                <asp:Label ID="LKEY" runat="server" Text="---"></asp:Label>
            </td>
            <td bgcolor="#99CCFF">
                &nbsp;</td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                Orange Data</td>
            <td class="style2" bgcolor="#99CCFF">
                <asp:Label ID="LKEY1" runat="server" Text="---"></asp:Label>
            </td>
            <td bgcolor="#99CCFF">
                &nbsp;</td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                &nbsp;</td>
            <td class="style2" bgcolor="#99CCFF">
                <asp:Button ID="Button3" runat="server" Text="ENCODE_AEX" 
                    onclick="Button3_Click"  />
                <asp:Button ID="Button4" runat="server" onclick="Button4_Click" 
                    Text="DECODE_AEX" />
            </td>
            <td bgcolor="#99CCFF">
                &nbsp;</td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                &nbsp;</td>
            <td class="style2" bgcolor="#99CCFF">
                <asp:Button ID="Button5" runat="server" onclick="Button4_Click" 
                    Text="LoadDLL" />
            </td>
            <td bgcolor="#99CCFF">
                &nbsp;</td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                &nbsp;</td>
            <td class="style2" bgcolor="#99CCFF">
                <asp:Label ID="Label3" runat="server" Text="Label"></asp:Label>
            </td>
            <td bgcolor="#99CCFF">
                &nbsp;</td>
        </tr>
        <tr>
            <td class="style16">
                Final KEY</td>
            <td class="style15">
                <asp:Label ID="LKEY0" runat="server" Text="---"></asp:Label>
            </td>
            <td class="style14">
                <asp:Label ID="Label1" runat="server" Text="GET:12490306"></asp:Label>
            </td>
        </tr>
        <tr>
            <td class="style1" bgcolor="#99CCFF">
                &nbsp;</td>
            <td class="style2" bgcolor="#99CCFF">
        <asp:Button ID="Button2" runat="server" Text="MAKE_MD5_HEX" 
                    onclick="Create_Click_MD5" />
            </td>
            <td bgcolor="#99CCFF">
                &nbsp;</td>
        </tr>
    </table>
    <p>
        &nbsp;</p>
    <p>
        <table style="width:100%;">
            <tr>
                <td class="style9" bgcolor="#CCFFCC">
                    TEST EXEMPLE</td>
                <td class="style10" bgcolor="#CCFFCC">
                    &nbsp;</td>
            </tr>
            <tr>
                <td class="style12" bgcolor="#CCFFCC">
                    Carrier Board ID</td>
                <td class="style13" bgcolor="#CCFFCC">
                    31701000</td>
            </tr>

            <tr>
                <td class="style12" bgcolor="#CCFFCC">
                    WIFI MAC</td>
                <td class="style13" bgcolor="#CCFFCC">
                    1CE19249001E</td>
            </tr>

            <tr>
                <td class="style12" bgcolor="#CCFFCC">
                    FPGA_A</td>
                <td class="style13" bgcolor="#CCFFCC">
                    002A108680143030<br />
                    002A10868014300A</td>
            </tr>

            <tr>
                <td class="style12" bgcolor="#CCFFCC">
                    FPGA_B</td>
                <td class="style13" bgcolor="#CCFFCC">
                    003A0E92D0630B08
                    <br />
                    00280F56D0102D24<br />
                    </td>
            </tr>

        </table>
    </p>
    <p>
        REF VICTORIA, ENGPWRID LOG:<br />
        <a href="file://w30server8/MDG/Project/Victoria/Task_Force/Production_Line/PilotRun_Log/EVT1/ENGPWRID/20160801">
        \\w30server8\MDG\Project\Victoria\Task_Force\Production_Line\PilotRun_Log\EVT1\ENGPWRID\20160801</a><br />
    </p>
    <p>
        REF VICTORIA, AMSDL LOG:<br />
        <a href="file://w30server8/MDG/Project/Victoria/Task_Force/Production_Line/PilotRun_Log/EVT1/ASMDL/20160804">
        \\w30server8\MDG\Project\Victoria\Task_Force\Production_Line\PilotRun_Log\EVT1\ASMDL\20160804</a></p>
    <p>
        &nbsp;</p>
    <p>
        &nbsp;</p>
    <p>
        <asp:Button ID="Button1" runat="server" Text="MD5_BASE64" 
            onclick="Create_Click" />
        </p>
    </form>
</body>
</html>

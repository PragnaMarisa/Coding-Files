<%-- Creating a connection to MySQL Database--%>

<%@ page import="java.sql.Connection, java.sql.DriverManager, java.sql.SQLException" %>
<%@ page import="java.sql.*" %>
<%@ include file="DatabaseConfiguration.jsp" %>

<%

if (session.getAttribute("user") == null)
{

    try 
    {
        Class.forName("com.mysql.jdbc.Driver");

        Connection connection = DriverManager.getConnection(url, username, password);
        session.setAttribute("user", connection);
    } 
    catch (Exception error) 
    {
        error.printStackTrace();
    }
}
%>

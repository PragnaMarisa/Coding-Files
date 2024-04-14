<%-- to return all the records to the js file --%>

<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>
<%@ page import="org.json.JSONArray" %>
<%@ page import="org.json.JSONObject" %>
<%@ page contentType="application/json; charset=UTF-8" %>
<%@ page import="java.io.*" %>
<%-- <%@ include file="MySQLConnection.jsp" %> --%>
<%@ include file="tableName.jsp" %>

<%

Connection connection = (Connection) session.getAttribute("user");
Statement statement = null;
ResultSet resultSet = null;

JSONArray itemsArray = new JSONArray();
String jsonResponse = "";

try {
    statement = connection.createStatement();
    String query = "SELECT * from " + viewName;
    resultSet = statement.executeQuery(query);
    
    ResultSetMetaData metaData = resultSet.getMetaData();
    String columnName = metaData.getColumnLabel(1);

    jsonResponse += "[";

    while (resultSet.next()) 
    {
       jsonResponse += resultSet.getString(columnName);
       jsonResponse += ",";
    }

    jsonResponse = jsonResponse.substring(0, jsonResponse.length() - 1);
    jsonResponse += "]";


} 
catch (SQLException error) 
{
    error.printStackTrace();
    jsonResponse = "{\"error\": \"Failed to retrieve data: " + error.getMessage() + "\"}";

} 
finally 
{
    try 
    {
        if (resultSet != null) resultSet.close();
        if (statement != null) statement.close();
    } 
    catch (SQLException error) 
    {
        error.printStackTrace();
        jsonResponse = "{\"error\": \"Failed to close resources: " + error.getMessage() + "\"}";
    }
}

out.print(jsonResponse);
%>

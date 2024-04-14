<%-- returns a json format of columns of a view and table--%>

<%@ page import="java.sql.*" %>
<%@ page import="org.json.JSONArray" %>
<%@ page import="org.json.JSONObject" %>
<%@ page contentType="application/json" %>
<%@ include file="MySQLConnection.jsp" %>
<%@ include file="tableName.jsp" %>

<%

Connection connection = (Connection) session.getAttribute("user");
PreparedStatement statement = null;
ResultSet resultSet = null;

JSONArray tableColumns = new JSONArray();
JSONArray viewColumns = new JSONArray();



try
{
	String query = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = ?";
	statement = connection.prepareStatement(query);
    statement.setString(1, viewName);

	resultSet = statement.executeQuery();

	if(resultSet.next()) 
	{
        String columnName = resultSet.getString("COLUMN_NAME");
        String[] columnNames = columnName.split("_");
        for (String name : columnNames) 
        {
            if (name.contains("0")) 
            { 
                name = name.substring(1);
            }
            else
            {

                tableColumns.put(name);
            }
            viewColumns.put(name);
        }

    }


}
catch (SQLException error) 
{
    error.printStackTrace();
} 

JSONObject result = new JSONObject();
result.put("tableColumns", tableColumns);
result.put("viewColumns", viewColumns);



out.print(result.toString());

%>
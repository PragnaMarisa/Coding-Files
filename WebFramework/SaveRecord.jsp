<%-- to save a record --%>

<%@ page import="java.sql.*" %>
<%@ page import="java.io.*" %>
<%@ page import="java.util.Collections" %>
<%@ page import="java.util.Arrays" %>
<%@ page contentType="application/json" %>
<%@ include file="tableName.jsp" %>


<%

String[] columnNames = (String[]) session.getAttribute(tableName);
String[] columnValues = new String[columnNames.length];;

for(int counter = 0; counter < columnNames.length; counter++)
{
    columnValues[counter] = request.getParameter(columnNames[counter]);
}

String jsonResponse = "";
Connection connection = (Connection) session.getAttribute("user");
PreparedStatement statement = null;
ResultSet resultSet = null;

try {
        String columnNamesStr = String.join(",", Arrays.asList(columnNames));
        String placeholders = String.join("','", Arrays.asList(columnValues));


        String query = "INSERT INTO " + tableName + "(" + columnNamesStr + ") VALUES('"+ placeholders + "') " +
                "ON DUPLICATE KEY UPDATE ";

        for (int i = 1; i < columnValues.length; i++) 
        {
            query += columnNames[i] + "=?,";
        }

        query = query.substring(0, query.length() - 1);

        statement = connection.prepareStatement(query);

        for (int i = 1; i < columnValues.length; i++) 
        {
            statement.setString(i, columnValues[i]);
        }

        int saveStatus = statement.executeUpdate();

        if (saveStatus > 0) {
            jsonResponse = "{\"error\": \"1\"}";
        } else {
            jsonResponse = "{\"error\": \"0\"}";
        }
    
} catch (SQLException error) {
    error.printStackTrace();
    jsonResponse = "{\"error\": \"00\", \"message\": \"SQL Error: " + error.getMessage() + "\"}";
} finally {
    try {
        if (resultSet != null) resultSet.close();
        if (statement != null) statement.close();
    } catch (SQLException error) {
        error.printStackTrace();
    }
}
out.print(jsonResponse);
%>

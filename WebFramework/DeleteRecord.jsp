<%@ page import="java.sql.*" %>
<%@ page contentType="application/json" %>
<%-- <%@ include file="MySQLConnection.jsp" %> --%>
<%@ include file="tableName.jsp" %>

<%

Connection connection = (Connection) session.getAttribute("user");
String key = request.getParameter("Key");
String value = request.getParameter("Value");

String jsonResponse = "{\"error\": \"0\"}";

PreparedStatement statement = null;

try
{
	String query = "DELETE FROM " + tableName + " WHERE " + key + "= ?";
	statement = connection.prepareStatement(query);
	statement.setString(1,value);

	int deleteStatus = statement.executeUpdate();
	if (deleteStatus > 0)
	{
		// success ayinappudu kuda error ena neeku haa acess cheyyadaniki annitiki error aney ichz
		// ila one line lo query rayocha
		jsonResponse = "{\"error\": \"1\"}";
	}
}
catch(Exception error)
{
	error.printStackTrace();
	out.println(error.getMessage());
}
finally
{
	try 
    {
        if (statement != null) statement.close();
    } 
    catch (SQLException error) 
    {
        error.printStackTrace();
		out.println(error.getMessage());
    }
}

out.print(jsonResponse);

%>
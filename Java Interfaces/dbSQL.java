// this uses SQL database for data storage
// this class implements the interface iCRUDS


import java.io.File;
import java.util.*;
import java.util.Scanner;
import java.sql.*;

class dbSQL implements iCRUDS
{
	private Connection connection;
    private Statement statement;
    private ResultSet resultSet;
	public dbSQL()
	{
		
		String server = "138.68.140.83";
        String database = "dbPragna";
        String username = "Pragna";
        String password = "Pragna@123";

        try 
        {
            connection = DriverManager.getConnection("jdbc:mysql://" + server + "/" + database, username, password);
            statement = connection.createStatement();
        } 
        catch (SQLException e) 
        {
            e.printStackTrace();
        }
	}
	

	
	public int create(List<Object> pfieldValues)
	{
        int createStatus = 0;
		try 
        {
            List<Object> fieldValues = pfieldValues;
            System.out.println(fieldValues);
            PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO tabItem (ItemId, Description, UnitPrice, StockQty, SupplierId) VALUES(?, ?, ?, ?, ?)");
            preparedStatement.setString(1, (String) fieldValues.get(0));
            preparedStatement.setString(2, (String) fieldValues.get(1));
            preparedStatement.setInt(3, (int) fieldValues.get(2));
            preparedStatement.setInt(4, (int) fieldValues.get(3));
            preparedStatement.setString(5, (String) fieldValues.get(4));
            createStatus = preparedStatement.executeUpdate();
        } 
        catch (Exception error) 
        {
            error.printStackTrace();
        }
        return createStatus;
	}

	public List<List<Object>> getAllRecords() 
    {
        List<List<Object>> data = new ArrayList<>();
        try 
        {
            ResultSet resultSet = statement.executeQuery("SELECT * FROM tabItem");

            if (resultSet.next()) 
            {
                do 
                {
                    List<Object> rowData = new ArrayList<>();
                    rowData.add(resultSet.getString("ItemId"));
                    rowData.add(resultSet.getString("Description"));
                    rowData.add(resultSet.getString("UnitPrice"));
                    rowData.add(resultSet.getString("StockQty"));
                    rowData.add(resultSet.getString("SupplierId"));
                    data.add(rowData);
                    // printItem(resultSet);
                } while (resultSet.next());
            } 
            else
            {
                System.out.println("No data in the database.");
            }

        } 
        catch (SQLException e) 
        {
            e.printStackTrace();
        }
        return data;
    }

    
}
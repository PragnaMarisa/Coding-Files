// this uses SQLite database for data storage
// this class implements the interface iCRUDS


import java.sql.*;
import java.util.Scanner;
import java.util.*;


public class dbSQLite implements iCRUDS
{
    public Connection connection;
    public Statement statement;

    public dbSQLite()
    {
        try 
        {
            String url = "jdbc:sqlite:C:\\Users\\my pc\\Downloads\\DMart.db";
            connection = DriverManager.getConnection(url);
            statement = connection.createStatement();
        } 
        catch (SQLException error) 
        {
            error.printStackTrace();
            return;
        }
    }

    
    public int create(List<Object> pFieldValues) 
    {
        int createStatus = 0;
        try 
        {
            List<Object> fieldValues = pFieldValues;
            PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO Item (ItemId, Description, UnitPrice, StockQty, SupplierId) VALUES(?, ?, ?, ?, ?)");
            preparedStatement.setString(1, (String) fieldValues.get(0));
            preparedStatement.setString(2, (String) fieldValues.get(1));
            preparedStatement.setInt(3, (int) fieldValues.get(2));
            preparedStatement.setInt(4, (int) fieldValues.get(3));
            preparedStatement.setString(5, (String) fieldValues.get(4));
            createStatus = preparedStatement.executeUpdate();
        } 
        catch (SQLException error) 
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
            ResultSet resultSet = statement.executeQuery("SELECT * FROM Item");
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();

            while (resultSet.next()) 
            {
                List<Object> rowData = new ArrayList<>();
                    rowData.add(resultSet.getString("ItemId"));
                    rowData.add(resultSet.getString("Description"));
                    rowData.add(resultSet.getString("UnitPrice"));
                    rowData.add(resultSet.getString("StockQty"));
                    rowData.add(resultSet.getString("SupplierId"));
                    data.add(rowData);
            }
        }
        catch (SQLException error) 
        {
            error.printStackTrace();
        }
    return data;
    }

}



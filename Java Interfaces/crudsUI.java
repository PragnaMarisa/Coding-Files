// user interface for CRUDs operations.

import java.util.Scanner;
import java.util.*;

public class crudsUI
{
	public List<Object> create()
	{
			List<Object> fieldValues = new ArrayList<>();
			Scanner scanner = new Scanner(System.in);
            System.out.print("Enter ItemId: ");
            String itemId = scanner.nextLine();
            fieldValues.add(itemId);
            System.out.print("Enter the item description: ");
            String description = scanner.nextLine();
            fieldValues.add(description);
            System.out.print(description + " UnitPrice: ");
            int unitPrice = Integer.parseInt(scanner.nextLine());
            fieldValues.add(unitPrice);
            System.out.print(description + " Stock Quantity: ");
            int stockQty = Integer.parseInt(scanner.nextLine());
            fieldValues.add(stockQty);
            System.out.print("Enter SupplierId: ");
            String supplierId = scanner.nextLine();
            fieldValues.add(supplierId);

            return fieldValues;
	}

	public void printCreateStatus(int pCreateStatus, List<Object> pfieldValues)
	{
		if (pCreateStatus == 1)
		{
			System.out.println("Successfully added an item with id " + (String) pfieldValues.get(0) + ".");
		}
		else
		{
			System.out.println("Unable to add a new item into your database.");
		}
	}

	public void showData(List<List<Object>> pData)
	{
		List<List<Object>> data = pData;
		for (List<Object> rowData : data) 
		{
			printRowData(rowData);         
        }
	}

	public void printRowData(List<Object> pRowData)
    {
        System.out.println("-----------------------------------------------------------------------");
        System.out.println("Item ID: " + pRowData.get(0));
        System.out.println("Description: " + pRowData.get(1));
        System.out.println(pRowData.get(1) + "Unit Price: " + pRowData.get(2));
        System.out.println(pRowData.get(1) + "Stock Quantity: " + pRowData.get(3));
        System.out.println(pRowData.get(1) + "Supplier ID: " + pRowData.get(4));
        System.out.println("-----------------------------------------------------------------------");
    }
}
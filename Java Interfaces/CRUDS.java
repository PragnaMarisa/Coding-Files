// testing iCRUDS interface.

import java.io.File;
import java.io.FileInputStream;
import java.util.Scanner;
import java.util.*;


public class CRUDS
{
	private static String classNameFile = "ClassName.cfg";
	public static void main(String[] args) 
	{
		try
		{
			File fpClassName = new File(classNameFile);
			FileInputStream fis = new FileInputStream(fpClassName);
			byte[] data = new byte[(int) fpClassName.length()];
			fis.read(data);
			fis.close();
			String className = new String(data, "UTF-8");
			iCRUDS oCRUDS = (iCRUDS)Class.forName(className).newInstance();
			showMenu(oCRUDS);

		}
		catch (Exception e)
		{
			System.out.println(e);
		}
	}

	private static void showMenu(iCRUDS oCRUDS)
	{
		crudsUI oUI = new crudsUI();
		while(true)
		{
		System.out.println("------ DMart ------");
		System.out.println("1. Add a item.");
		System.out.println("2. Show all items.");
		System.out.println("3. Exit.");
		Scanner scanner = new Scanner(System.in);
		System.out.println("Enter your choice: ");
		int choice = Integer.parseInt(scanner.nextLine());
		switch(choice)
		{
			case 1: List<Object> fieldValues = oUI.create();
					System.out.println(fieldValues);
					int createStatus = oCRUDS.create(fieldValues);
					oUI.printCreateStatus(createStatus, fieldValues);
					break;
			case 2: List<List<Object>> data = oCRUDS.getAllRecords();
					oUI.showData(data);
					break;
			case 3: System.exit(0);
			default: System.out.println("Invalid choice.");
		}
		} 

	}
}

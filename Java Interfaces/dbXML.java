// this uses SQL database for data storage
// this class implements the interface iCRUDS


import java.io.File;
import java.io.FileWriter;
import java.util.*;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

class dbXML implements iCRUDS 
{
    public int create(List<Object> pfieldValues) 
    {
        int createStatus = 0;
        try 
        {
            List<Object> fieldValues = pfieldValues;

            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.newDocument();

            Element rootElement = doc.createElement("Items");
            doc.appendChild(rootElement);   

            Element itemElement = doc.createElement("Item");
            rootElement.appendChild(itemElement);

            String[] fieldNames = {"ItemId", "Description", "UnitPrice", "StockQty", "SupplierId"};
            for (int counter = 0; counter < fieldNames.length; counter++) 
            {
                Element fieldElement = doc.createElement(fieldNames[counter]);
                fieldElement.appendChild(doc.createTextNode(fieldValues.get(counter).toString()));
                itemElement.appendChild(fieldElement);
            }
            createStatus = 1;

            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);
            StreamResult result = new StreamResult(new File("items.xml"));
            transformer.transform(source, result);
            
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
            File xmlFile = new File("items.xml");
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(xmlFile);

            doc.getDocumentElement().normalize();
            NodeList nodeList = doc.getElementsByTagName("Item");

            System.out.println("Items:");
            for (int counter = 0; counter < nodeList.getLength(); counter++) {
                Element element = (Element) nodeList.item(counter);
                List<Object> rowData = new ArrayList<>();
                rowData.add(element.getElementsByTagName("ItemId").item(0).getTextContent());
                rowData.add(element.getElementsByTagName("Description").item(0).getTextContent());
                rowData.add(element.getElementsByTagName("UnitPrice").item(0).getTextContent());
                rowData.add(element.getElementsByTagName("StockQty").item(0).getTextContent());
                rowData.add(element.getElementsByTagName("SupplierId").item(0).getTextContent());
                data.add(rowData);
            }
        } 
        catch (Exception error) 
        {
            error.printStackTrace();
        }
        return data;
    }
}


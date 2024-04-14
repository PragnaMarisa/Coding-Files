// javascript that handle multiple jsp files.


let tableColumnNames = null;
let viewColumnNames = null;
let inputValues = [];
let table = null;


async function load()
{
    try{

        await getColumnNames();
        await createForm();
        await getAllRecords();
    }
    catch(error)
    {

        console.error("Error occurred:", error);
    }
}

async function getColumnNames()
{
    const query = "GetColumnNames.jsp"
    try{
        const response = await fetch(query);
        const result = await response.json();
        tableColumnNames = result.tableColumns;
        viewColumnNames = result.viewColumns;
    }
    catch(error)
    {

        console.error("Error occurred:", error);
    }

}

async function createForm()
{

    var form = document.createElement("form");
    form.id = "inputForm";
    form.addEventListener("submit", handleSubmit); 

    var heading = document.createElement("h3");
    table = tableColumnNames[0].slice(0, -2);
    heading.textContent = "DMart " + table + "s";
    form.appendChild(heading);

    for (var counter = 0; counter < tableColumnNames.length; counter++) {
        var label = document.createElement("label");
        label.setAttribute("for", tableColumnNames[counter]);
        label.textContent = tableColumnNames[counter] + ":  ";

        var input = document.createElement("input");
        input.type = "text";
        input.name = tableColumnNames[counter];
        input.id = tableColumnNames[counter];
        input.placeholder = "Enter " + tableColumnNames[counter];

        form.appendChild(label);
        form.appendChild(input);
        form.appendChild(document.createElement("br")); 
    }

    var submitButton = document.createElement("button");
    submitButton.type = "submit";
    submitButton.textContent = "Save";
    form.appendChild(submitButton);

    var inputArea = document.getElementById("InputArea");
    inputArea.appendChild(form);

}

async function getInputValues() {

    inputValues = [];
    
    tableColumnNames.forEach(columnName => {
        const inputElement = document.getElementById(columnName);
        if (inputElement) {
            inputValues.push(inputElement.value);
        } else {
            inputValues.push(null); 
        }
    });
    return inputValues;
}



async function saveRecord() 
{
    getInputValues();
    try{
        console.log(inputValues);

        let query = "SaveRecord.jsp?";

        for(let counter = 0; counter < tableColumnNames.length; counter++)
        {
            query += tableColumnNames[counter] + "=" + inputValues[counter] + "&";
        }

        query = query.substring(0, query.length - 1);
        console.log(query);
        const response = await fetch(query);
        const returnValue = await response.json();
        let status = returnValue.error;
        console.log(status);
        if (status > 0) {
            alert(table + " saved successfully.");
            clearData();
            getAllRecords();
        } else {
            alert( table + " not saved! Retry again.");
        }
    } catch (error) {
        console.error("Error occurred:", error);
    }
}

function handleSubmit(event) 
{
        event.preventDefault();
        saveRecord();
}

function  clearData() 
{
    document.querySelectorAll('input[type="text"]').forEach(input => input.value);
}


async function getAllRecords()
{
    const query = "GetAllRecords.jsp";

    try 
    {
        const response = await fetch(query);
        const products = await response.json();

        var dataTable = await createTable(products);
        var tableDiv = document.getElementById("ResultArea");
        tableDiv.innerHTML='';
        tableDiv.appendChild(dataTable);

        document.getElementById("ResultArea").querySelectorAll('.editButton').forEach(function(button) {
                    button.addEventListener('click', function() {
                        populateRow(this.closest('tr'));
                    });
                }); 

        document.getElementById("ResultArea").querySelectorAll('.deleteButton').forEach(function(button) {
            button.addEventListener('click', async function() {
                const Id = this.closest('tr').querySelector('td:first-child').textContent;
                    deleteItem(this, Id);
            });
        });

    } catch (error) {
        console.error("Error occurred:", error);
        document.getElementById("ResultArea").innerHTML = "Failed to fetch details. Error: " + error.message;
    }
}

async function addRow(pRecord) {
    var row = document.createElement("tr");
    viewColumnNames.forEach(function(columnName) {
        var cell = document.createElement("td");
        if (!tableColumnNames.includes(columnName)) {
            cell.innerHTML = pRecord[columnName];
        } else {
            cell.textContent = pRecord[columnName];
        }
        row.appendChild(cell);
    });
    return row;
}

async function createTable(pRecords) {
    var table = document.createElement("table");
    table.id = "ResultTable";
    table.name = "ResultTable";

    var thead = document.createElement("thead");
    var headerRow = document.createElement("tr");
    viewColumnNames.forEach(function(columnName) {
        var headerCell = document.createElement("th");
        headerCell.textContent = columnName;
        headerRow.appendChild(headerCell);
    });
    thead.appendChild(headerRow);
    table.appendChild(thead);

    var tbody = document.createElement("tbody");
    pRecords.forEach(async function(pRecord) {
        var newRow = await addRow(pRecord, viewColumnNames);
        tbody.appendChild(newRow);
    });
    table.appendChild(tbody);

    return table;
}


async function deleteItem(pButton, pKey) {

    pButton = pButton.parentNode.parentNode;

    let choice = confirm("Are you sure want to delete?");
    if(choice)
    {
        console.log(tableColumnNames[0]);
        console.log(pKey);
        const query = "DeleteRecord.jsp?&Key=" + tableColumnNames[0] + "&Value=" + pKey;
        console.log(query);
        const response = await fetch(query);
        const error = await response.json();
        console.log(error);
        let status = error.error;
        if (status > 0 )
        {
            alert("Successfully deleted "+ table + " with " + table + "Id "+ pKey + " !");
            pButton.remove();
        }
        else
        {
            alert("Unable to delete "+ table + " with " + table + "Id"+ pKey + " !");
        }
    }
}


function populateRow(pRow) 
{
    const tdElements = pRow.getElementsByTagName('td');
    const data = Array.from(tdElements).map(td => td.textContent);

    tableColumnNames.forEach((id, index) => {
        document.getElementById(id).value = data[index];
    });
}

// CREATE VIEW viewSupplier AS
// SELECT JSON_MERGE_PATCH(
//     JSON_OBJECT(
//         "SupplierId", SupplierId,
//         "SupplierName", SupplierName
//     ),
//     JSON_OBJECT("Operations", CONCAT(
//         "<button class='editButton'>Edit</button>",
//         "<button class='deleteButton'>Delete</button>"
//     ))
// ) AS SupplierId_SupplierName_Operations
// FROM tabSupplier;







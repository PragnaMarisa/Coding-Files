// An interface named iCRUDS, to implemennt all the CRUDS operations.

import java.util.*;


interface iCRUDS
{
	int create(List<Object> fieldValues);
	List<List<Object>> getAllRecords();
}


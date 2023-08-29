/*#include<iostream>
#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include<readline/history.h>
#include<cstring>


int main(int argc, char *argv[]) {
  Disk disk_run;
  
//------------STAGE 1 PRINT HELLO CODE

  //unsigned char buffer[BLOCK_SIZE];
  //Disk::readBlock(buffer, 7000);
  //char message[] = "hello";
  //memcpy(buffer + 20, message, 6);
  //Disk::writeBlock(buffer, 7000);

  //unsigned char buffer2[BLOCK_SIZE];
  //char message2[6];
  //Disk::readBlock(buffer2, 7000);
  //memcpy(message2, buffer2 + 20, 6);
  //std::cout << message2;
  
  //----------EXERCISE QUESTION OF STAGE 1 PRINTING BLOCK SIZE
  
//unsigned char buffer3[BLOCK_SIZE];

    //Disk::readBlock(buffer3,0);
    
    //for(int i=0;i<=BLOCK_SIZE;i++)
        //std::cout<<static_cast<int>(buffer3[i])<<" ";
  //return 0;

//----------MAIN.CPP FILE OF STAGE 2-----------------------------------------------------------------------------------------------------------------------------------------------------
  // create objects for the relation catalog and attribute catalog
  /*
  RecBuffer relCatBuffer(RELCAT_BLOCK);//object 
  //RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

  HeadInfo relCatHeader;//for header
  //HeadInfo attrCatHeader;
  

  // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // (we will implement these functions later)
  relCatBuffer.getHeader(&relCatHeader);
  //attrCatBuffer.getHeader(&attrCatHeader);
 int totalRelations=relCatHeader.numEntries;
  //int totalAttributes=attrCatHeader.numEntries;
  for (int i=0;i<totalRelations;i++) {

    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);//ith position slot gets loaded into relCatRecord

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);
    int num=ATTRCAT_BLOCK;
    while(num!=-1)
{
 RecBuffer attrCatBuffer(num);
 HeadInfo attrCatHeader;
 attrCatBuffer.getHeader(&attrCatHeader);
    int totalAttributes=attrCatHeader.numEntries;

    for (int j = 0; j <totalAttributes;j++) {

      // declare attrCatRecord and load the attribute catalog entry into it
      Attribute attrCatRecord[RELCAT_NO_ATTRS];
     attrCatBuffer.getRecord(attrCatRecord,j);
      if (attrCatRecord[ATTRCAT_REL_NAME_INDEX].nVal==relCatRecord[RELCAT_REL_NAME_INDEX].nVal) {
      
        const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
        const char *attrName=attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal;
        if(!strcmp(attrName,"Class"))
        {
           strcpy(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal , "Batch");
        }
        printf("  %s: %s\n", /* get the attribute name //attrName, attrType);
   /*   }
    }
    num=attrCatHeader.rblock;
    }
    printf("\n");
  }
  
  printf("/n");

  return 0;
}
*/
//---------------------------------------------------------------------------------STAGE 3 ----------------------------------------------------------------------------------
/*
#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include<iostream>


int main(int argc, char *argv[]) 
{
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;

  
 // for i = 0 and i = 1 (i.e RELCAT_RELID and ATTRCAT_RELID)
  for(int i=0;i<=2;i++)
  {
    //i=0  ->  RELCAT_ID
    //i=1  ->  ATTRCAT_ID
     
     RelCatEntry RelCatBuffer;
     RelCacheTable::getRelCatEntry(i,&RelCatBuffer);
     printf("Relation : %s\n ", RelCatBuffer.relName);

     for(int j=0;j<RelCatBuffer.numAttrs;j++)
     
     {
         AttrCatEntry AttrCatBuffer;
         AttrCacheTable::getAttrCatEntry(i,j,&AttrCatBuffer);
         const char *attrType = AttrCatBuffer.attrType == NUMBER ? "NUM" : "STR";
			   printf (" %s: %s\n", AttrCatBuffer.attrName, attrType);

     }

     printf("\n");

  }
      // get the relation catalog entry using RelCacheTable::getRelCatEntry()
      // printf("Relation: %s\n", relname);

      // for j = 0 to numAttrs of the relation - 1
      //     get the attribute catalog entry for (rel-id i, attribute offset j)
      //      in attrCatEntry using AttrCacheTable::getAttrCatEntry()

      //     printf("  %s: %s\n", attrName, attrType);
  

  return 0;
}
*/
#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"

// local headers
#include <iostream>

void printBuffer(unsigned char buffer[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << (int)buffer[i] << " ";
		if (i % 64 == 63)
			std::cout << "\n";
	}
	std::cout << "\n";
}

void printAttributeCatalog () {
	// create objects for the relation catalog and attribute catalog
	RecBuffer relCatBufferfer(RELCAT_BLOCK);
	RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

	// creating headers for relation catalog and attribute catalog
	HeadInfo relCatHeader;
	HeadInfo attrCatHeader;

	// load the headers of both the blocks into relCatHeader and attrCatHeader.
	// (we will implement these functions later)
	relCatBufferfer.getHeader(&relCatHeader);
	attrCatBuffer.getHeader(&attrCatHeader);

	// attrCatBaseSlot stores the index of current slot, 
	// which is incremented everytime an attribute entry 
	// is handled
	for (int i = 0, attrCatSlotIndex = 0; i < relCatHeader.numEntries; i++)
	{
		// will store the record from the relation catalog
		Attribute relCatRecord[RELCAT_NO_ATTRS]; 
		relCatBufferfer.getRecord(relCatRecord, i);

		printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

		int j = 0;
		for (; j < relCatRecord[RELCAT_NO_ATTRIBUTES_INDEX].nVal; j++, attrCatSlotIndex++)
		{
			// declare attrCatRecord and load the attribute catalog entry into it
			Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
			attrCatBuffer.getRecord(attrCatRecord, attrCatSlotIndex);

			// if the current attribute belongs to the current relation
			// then we print it, which is checked by comparing names
			if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,
					   relCatRecord[RELCAT_REL_NAME_INDEX].sVal) == 0)
			{
				const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER
										   ? "NUM" : "STR";
				printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
			}

			// once all the slots are traversed, we update the block number
			// of the attrCatBuffer to the next block, and then attrCatHeader
			// is updated to the header of next block
			if (attrCatSlotIndex == attrCatHeader.numSlots-1) {
				attrCatSlotIndex = -1; // implementational operation, since the loop will increment anyways
				attrCatBuffer = RecBuffer (attrCatHeader.rblock);
				attrCatBuffer.getHeader(&attrCatHeader);
			}
		}

		printf("\n");
	}
}

void updateAttributeName (const char* relName, 
									const char* oldAttrName, const char* newAttrName) {
	// used to hold reference to the block which referred to 
	// for getting records, headers and updating them
	RecBuffer attrCatBuffer (ATTRCAT_BLOCK);
	
	HeadInfo attrCatHeader;
	attrCatBuffer.getHeader(&attrCatHeader);

	// iterating the records in the Attribute Catalog
	// to find the correct entry of relation and attribute
	for (int recIndex = 0; recIndex < attrCatHeader.numEntries; recIndex++) {
		Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
		attrCatBuffer.getRecord(attrCatRecord, recIndex);

		// matching the relation name, and attribute name
		if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, relName) == 0
			&& strcmp(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, oldAttrName) == 0) 
		{
			strcpy(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, newAttrName);
			attrCatBuffer.setRecord(attrCatRecord, recIndex);
			std::cout << "Update successful!\n\n";
			break;
		}

		// reaching at the end of the block, and thus loading
		// the next block and setting the attrCatHeader & recIndex
		if (recIndex == attrCatHeader.numSlots-1) {
			recIndex = -1;
			attrCatBuffer = RecBuffer (attrCatHeader.rblock);
			attrCatBuffer.getHeader(&attrCatHeader);
		}
	}

}

int main(int argc, char *argv[])
{
	Disk disk_run;
	StaticBuffer bufferCache;
	OpenRelTable cache;

	// printAttributeCatalog();
	// updateAttributeName ("Students", "Class", "Batch");
	// printAttributeCatalog();

	for (int relId = 0; relId <= 2; relId++) {
		// i = 0 -> RELCAT_RELID
		// i = 1 -> ATTRCAT_RELID

		RelCatEntry relCatBuffer;
		RelCacheTable::getRelCatEntry(relId, &relCatBuffer);

		printf ("Relation: %s\n", relCatBuffer.relName);

		for (int attrIndex = 0; attrIndex < relCatBuffer.numAttrs; attrIndex++) {
			AttrCatEntry attrCatBuffer;
			AttrCacheTable::getAttrCatEntry(relId, attrIndex, &attrCatBuffer);

			const char *attrType = attrCatBuffer.attrType == NUMBER ? "NUM" : "STR";
			printf ("    %s: %s\n", attrCatBuffer.attrName, attrType);
		}
		printf("\n");
	}

	return 0;
}
  

/*#include "OpenRelTable.h"

#include <cstring>
#include<cstdlib>
#include<stdio.h>

AttrCacheEntry* createnewnode(){
  AttrCacheEntry *node;
  node=(AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
  //node->next=nullptr;
  return node;
}

AttrCacheEntry* createlinkedlist(int n){
  AttrCacheEntry *temp=nullptr,*t=nullptr;
  temp = createnewnode();
  n--;
  t=temp;
  while(n--){
    temp->next=createnewnode();
    temp=temp->next;
  }
  temp->next=nullptr;
  return t;
}

OpenRelTable::OpenRelTable() {

  // initialize relCache and attrCache with nullptr
  for (int i = 0; i < MAX_OPEN; ++i) {
    RelCacheTable::relCache[i] = nullptr;
    AttrCacheTable::attrCache[i] = nullptr;
  }

  /**** Setting up Relation Cache entries ****/
  // (we need to populate relation cache with entries for the relation catalog
  //  and attribute catalog.)

  /** setting up Relation Catalog relation in the Relation Cache Table**//*
  RecBuffer relCatBlock(RELCAT_BLOCK);

  Attribute relCatRecord[RELCAT_NO_ATTRS];

  for(int slotnum=0;slotnum<3;slotnum++){
    
    relCatBlock.getRecord(relCatRecord, slotnum/*RELCAT_SLOTNUM_FOR_RELCAT*//*);

    struct RelCacheEntry relCacheEntry;
    RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
    relCacheEntry.recId.block = RELCAT_BLOCK;
    relCacheEntry.recId.slot =slotnum /*RELCAT_SLOTNUM_FOR_RELCAT*/;

  // allocate this on the heap because we want it to persist outside this function
 /*   RelCacheTable::relCache[slotnum] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
    *(RelCacheTable::relCache[slotnum]) = relCacheEntry;
  }
  /** setting up Attribute Catalog relation in the Relation Cache Table **/

  
  
  /**** Setting up Attribute cache entries ****/
  // (we need to populate attribute cache with entries for the relation catalog
  //  and attribute catalog.)

  /** setting up Relation Catalog relation in the Attribute Cache Table **/
  /*RecBuffer attrCatBlock(ATTRCAT_BLOCK);

  Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  struct AttrCacheEntry *attrCacheEntry,*Head=nullptr;
  // iterate through all the attributes of the relation catalog and create a linked
  int entry=0;

  for (int slotnum=0;slotnum<=2;slotnum++){
  int nofAttr=RelCacheTable::relCache[slotnum]->relCatEntry.numAttrs;
  Head=createlinkedlist(nofAttr);
  attrCacheEntry=Head;
  // list of AttrCacheEntry (slots 0 to 5)
  // for each of the entries, set
    for(;nofAttr>0;entry++,nofAttr--)
    {
      attrCatBlock.getRecord(attrCatRecord,entry);

      AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &(attrCacheEntry->attrCatEntry));
      attrCacheEntry->recId.block = ATTRCAT_BLOCK;
      attrCacheEntry->recId.slot = entry;
     //attrCacheEntry.next=t->next;
     //t=&attrCacheEntry;
    // NOTE: allocate each entry dynamically using malloc

    // set the next field in the last entry to nullptr
      attrCacheEntry=attrCacheEntry->next;
  }
    AttrCacheTable::attrCache[slotnum] = Head/* head of the linked list *//*;
  }
  
}

OpenRelTable::~OpenRelTable() {
  // free all the memory that you allocated in the constructor
}
*/

#include "OpenRelTable.h"

#include <cstring>
#include <stdlib.h>
#include <stdio.h>

AttrCacheEntry* createAttrCacheEntryList (int size) {
    AttrCacheEntry *head = nullptr, *curr = nullptr;
    head = curr = (AttrCacheEntry*) malloc (sizeof(AttrCacheEntry));
    size--;
    while (size--) {
        curr->next = (AttrCacheEntry*) malloc (sizeof(AttrCacheEntry));
        curr = curr->next;
    }
    curr->next = nullptr;

    return head;
}

OpenRelTable::OpenRelTable()
{

    // initialize relCache and attrCache with nullptr
    for (int i = 0; i < MAX_OPEN; ++i)
    {
        RelCacheTable::relCache[i] = nullptr;
        AttrCacheTable::attrCache[i] = nullptr;
    }

    /************ Setting up Relation Cache entries ************/
    // (we need to populate relation cache with entries for the relation catalog
    //  and attribute catalog.)

    // setting up the variables
    RecBuffer relCatBlock (RELCAT_BLOCK);
    Attribute relCatRecord [RELCAT_NO_ATTRS];
    RelCacheEntry *relCacheEntry = nullptr;

    for (int relId = RELCAT_RELID; relId <= ATTRCAT_RELID+1; relId++) {
        relCatBlock.getRecord(relCatRecord, relId);

        relCacheEntry = (RelCacheEntry *) malloc (sizeof(RelCacheEntry));
        RelCacheTable::recordToRelCatEntry(relCatRecord, &(relCacheEntry->relCatEntry));
        relCacheEntry->recId.block = RELCAT_BLOCK;
        relCacheEntry->recId.slot = relId;

        RelCacheTable::relCache[relId] = relCacheEntry;
    }

    
    /************ Setting up Attribute cache entries ************/
    // (we need to populate attribute cache with entries for the relation catalog
    //  and attribute catalog.)

    // setting up the variables
    RecBuffer attrCatBlock (ATTRCAT_BLOCK);
    Attribute attrCatRecord [ATTRCAT_NO_ATTRS];
    AttrCacheEntry *attrCacheEntry = nullptr, *head = nullptr;

    for (int relId = RELCAT_RELID, recordId = 0; relId <= ATTRCAT_RELID+1; relId++) {
        int numberOfAttributes = RelCacheTable::relCache[relId]->relCatEntry.numAttrs;
        head = createAttrCacheEntryList (numberOfAttributes);
        attrCacheEntry = head;
        
        while (numberOfAttributes--) {
            attrCatBlock.getRecord(attrCatRecord, recordId);

            AttrCacheTable::recordToAttrCatEntry(
                attrCatRecord, 
                &(attrCacheEntry->attrCatEntry)
            );
            attrCacheEntry->recId.slot = recordId++;
            attrCacheEntry->recId.block = ATTRCAT_BLOCK;

            attrCacheEntry = attrCacheEntry->next;
        }

        AttrCacheTable::attrCache[relId] = head;
    }

    /*
    RecBuffer relCatBuffer (RELCAT_BLOCK);
    Attribute relCatRecord [RELCAT_NO_ATTRS];

    HeadInfo relCatHeader;
    relCatBuffer.getHeader(&relCatHeader);

    int relationIndex = -1;
    char* relationName = "Students";

    for (int index = 2; index < relCatHeader.numEntries; index++) {
        relCatBuffer.getRecord(relCatRecord, index);

        if (strcmp(relCatRecord[RELCAT_REL_NAME_INDEX].sVal, 
                relationName) == 0) { // matching the name of the record we want
            relationIndex = index;
        }
    }

    if (relationIndex == -1) {
        printf("Relation \"%s\" does not exist!\n", relationName);
        // return;
    }
    else {
        
    }
    */
}

OpenRelTable::~OpenRelTable()
{
    // free all the memory that you allocated in the constructor
}

/*----------------------------------------------------------------------------STAGE 2--------------------------------------------------------------------------------------------------------------*/

//#include "BlockAccess.h"
/*
#include <cstring>
#include "BlockBuffer.h"
#include <cstdlib>


BlockBuffer::BlockBuffer(int blockNum) {
    this->blockNum = blockNum;
}

// calls the parent class constructor
RecBuffer::RecBuffer(int blockNum) : BlockBuffer::BlockBuffer(blockNum) {}

// load the block header into the argument pointer intialising an array in buffer 
int BlockBuffer::getHeader(struct HeadInfo *head) {//func 
  unsigned char buffer[BLOCK_SIZE];

  // read the block at this.blockNum into the buffer
  Disk::readBlock(buffer,this->blockNum);

  // populate the numEntries, numAttrs and numSlots fields in *head
  memcpy(&head->numSlots, buffer + 24, 4);//loading header in buffer to new header pointer.
  memcpy(&head->numEntries,buffer+16, 4);
  memcpy(&head->numAttrs,buffer+20, 4);
  memcpy(&head->rblock,buffer+12, 4);
  memcpy(&head->lblock,buffer+8, 4);

  return SUCCESS;
}

// load the record at slotNum into the argument pointer
int RecBuffer::getRecord(union Attribute *rec, int slotNum) {//Record ni rec union attribute loki load chyali,func used to find particular record in a blk which is loaded to buffer
  struct HeadInfo head;

  // get the header using this.getHeader() function
  this->getHeader(&head);

  int attrCount = head.numAttrs;
  int slotCount = head.numSlots;
  
  unsigned char buffer[BLOCK_SIZE];
  // read the block at this.blockNum into a buffer
  Disk::readBlock(buffer,this->blockNum);

  /* record at slotNum will be at offset HEADER_SIZE + slotMapSize + (recordSize * slotNum)
     - each record will have size attrCount * ATTR_SIZE
     - slotMap will be of size slotCount 
  
  int recordSize = attrCount * ATTR_SIZE;
  int offset = 32 + slotCount + (recordSize * slotNum);
  unsigned char *slotPointer = buffer + offset;//buffer is starting position of the block in buffer

  // load the record into the rec data structure
  memcpy(rec, slotPointer, recordSize);

  return SUCCESS;
}



*/

//-----------------------------------------------------------------------------STAGE 3-----------------------------------------------------------------------------------------------------------------
#include "BlockBuffer.h"

#include <cstdlib>
#include <cstring>
// the declarations for these functions can be found in "BlockBuffer.h"

BlockBuffer::BlockBuffer(int blockNum) {
 // initialise this.blockNum with the argument
     this->blockNum=blockNum;
}

// calls the parent class constructor
RecBuffer::RecBuffer(int blockNum) : BlockBuffer::BlockBuffer(blockNum) {}

// load the block header into the argument pointer
int BlockBuffer::getHeader(struct HeadInfo *head) {
 // unsigned char buffer[BLOCK_SIZE];

  // read the block at this.blockNum into the buffer
 //  Disk::readBlock(buffer,this->blockNum);
  // populate the numEntries, numAttrs and numSlots fields in *head
   unsigned char *bufferPtr;
  int ret = loadBlockAndGetBufferPtr(&bufferPtr);
  if (ret != SUCCESS) {
    return ret;   // return any errors that might have occured in the process
  }

   memcpy(&head->pblock, bufferPtr + 4, 4);
   memcpy(&head->lblock, bufferPtr+8, 4);
   memcpy(&head->rblock, bufferPtr+12/* fill this */, 4);
   memcpy(&head->numEntries, bufferPtr +16/* fill this */, 4);
   memcpy(&head->numAttrs, bufferPtr +20/* fill this */, 4);
   memcpy(&head->numSlots, bufferPtr + 24, 4);
  
  return SUCCESS;
}

// load the record at slotNum into the argument pointer
int RecBuffer::getRecord(union Attribute *rec, int slotNum) {
  struct HeadInfo head;

  // get the header using this.getHeader() function
  BlockBuffer::getHeader(&head);

  int attrCount = head.numAttrs;
  int slotCount = head.numSlots;

  // read the block at this.blockNum into a buffer
  
  // unsigned char buffer[BLOCK_SIZE];
  //  Disk::readBlock(buffer,this->blockNum);

  unsigned char *bufferPtr;
  int ret = loadBlockAndGetBufferPtr(&bufferPtr);
  if (ret != SUCCESS) {
    return ret;
  }

  /* record at slotNum will be at offset HEADER_SIZE + slotMapSize + (recordSize * slotNum)
     - each record will have size attrCount * ATTR_SIZE
     - slotMap will be of size slotCount
  */

  int recordSize = attrCount * ATTR_SIZE;
  unsigned char *slotPointer = bufferPtr +32 + slotCount+(recordSize*slotNum)/*calculate buffer + offset */;

  // load the record into the rec data structure
  memcpy(rec, slotPointer, recordSize);

  return SUCCESS;
}

// load the record at slotNum into the argument pointer
int RecBuffer::setRecord(union Attribute *rec, int slotNum)
{
	// get the header using this.getHeader() function
	struct HeadInfo head;
	BlockBuffer::getHeader(&head);

	int attrCount = head.numAttrs;
	int slotCount = head.numSlots;

	// read the block at this.blockNum into a buffer
	unsigned char *bufferPtr;
	// Disk::readBlock(buffer, this->blockNum);
	int ret = loadBlockAndGetBufferPtr(&bufferPtr);
	if (ret != SUCCESS)
		return ret;

	/* record at slotNum will be at offset HEADER_SIZE + slotMapSize + (recordSize * slotNum)
	   - each record will have size attrCount * ATTR_SIZE
	   - slotMap will be of size slotCount
	*/
	int recordSize = attrCount * ATTR_SIZE;
	unsigned char *slotPointer = bufferPtr + (32 + slotCount + (recordSize * slotNum)); // calculate buffer + offset

	// load the record into the rec data structure
	memcpy(slotPointer, rec, recordSize);

	Disk::writeBlock(bufferPtr, this->blockNum);

	return SUCCESS;
}

int BlockBuffer::loadBlockAndGetBufferPtr(unsigned char **buffPtr) {
  // check whether the block is already present in the buffer using StaticBuffer.getBufferNum()
  int bufferNum = StaticBuffer::getBufferNum(this->blockNum);

  if (bufferNum == E_BLOCKNOTINBUFFER) {
    bufferNum = StaticBuffer::getFreeBuffer(this->blockNum);

    if (bufferNum == E_OUTOFBOUND) {
      return E_OUTOFBOUND;
    }
    if (bufferNum == E_OUTOFBOUND || bufferNum == FAILURE)
			return FAILURE;


    Disk::readBlock(StaticBuffer::blocks[bufferNum], this->blockNum);
  }

  // store the pointer to this buffer (blocks[bufferNum]) in *buffPtr
  *buffPtr = StaticBuffer::blocks[bufferNum];

  return SUCCESS;
}

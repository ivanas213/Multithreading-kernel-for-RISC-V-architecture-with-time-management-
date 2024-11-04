
#include "../h/MemoryAllocator.h"
Mem* MemoryAllocator::head= nullptr;
MemoryAllocator::MemoryAllocator() {
    if(head== nullptr){

        head=(Mem*)(HEAP_START_ADDR);
       // size_t sz=(size_t)HEAP_END_ADDR-(size_t)HEAP_START_ADDR;
        head->size=(size_t)HEAP_END_ADDR-(size_t)HEAP_START_ADDR;
        head->next=nullptr;
        head->free=true;





    }


}

MemoryAllocator MemoryAllocator::getMemoryAllocator() {

    if(head==nullptr) {
        MemoryAllocator m;
        memoryAllocator=m;
    }
    return memoryAllocator;
}

void *MemoryAllocator::mem_alloc(size_t size) {
    size_t ost= size% MEM_BLOCK_SIZE;
    size_t sz;
    if(ost==0) sz=size+sizeof(Mem);
    else sz= size +sizeof(Mem) +MEM_BLOCK_SIZE- ost;

    size_t min=(size_t)HEAP_END_ADDR-(size_t)HEAP_START_ADDR;

    Mem* ok=nullptr;
    for(Mem* tek=head; tek; tek=tek->next){
        //pronasli gde moze i proveravamo da li je najbolje
        if(sz<=tek->size && tek->size-sz<=min && tek->free) {
            min=tek->size-sz;
            ok=tek;
            //if(sz==tek->size) full=true;
        }
    }
    if(ok) {
        if(min<=sizeof(Mem)){
            ok->free=false;
            ok->size+=min;
        }
        else{
            Mem* pom=(Mem*)((size_t )ok+sz);

            pom->free=true;

            pom->next=ok->next;

            pom->size=ok->size-sz;
            ok->free=false;
            ok->size=sz;
            ok->next=pom;
        }
        return (void*)((size_t )ok+sizeof(Mem));
    }
    return nullptr;




}


int MemoryAllocator::mem_free(void *base) {
    Mem* tek;
    Mem* prev= nullptr;
    for(tek=head;tek;prev=tek,tek=tek->next){
        if(!tek->free && (size_t)tek+sizeof(Mem)==(size_t)base) break;
    }
    if(!tek) return -1;
    tek->free=true;
    if(tek->next){
        if(tek->next->free && (char*)tek->next==(char*)tek+tek->size){
            tek->size=tek->size+tek->next->size;
            tek->next=tek->next->next;
        }
    }
    if(prev) if(prev->free && (char*)prev->next==(char*)prev+prev->size){
            prev->size=prev->size+prev->next->size;
            prev->next=prev->next->next;
    }
    return 0;
}
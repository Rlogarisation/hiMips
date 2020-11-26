// Simulate LRU replacement of page frames

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


// represent an entry in a simple inverted page table

typedef struct ipt_entry {
    int virtual_page;        // == -1 if physical page free
    int last_access_time;
} ipt_entry_t;


void lru(int n_physical_pages, int n_virtual_pages);
void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt);
bool exists(int virtual_page, int n_physical_pages, struct ipt_entry *ipt);
bool isFree(int virtual_page, int n_physical_pages, struct ipt_entry *ipt);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    lru(atoi(argv[1]), atoi(argv[2]));
    return 0;
}


void lru(int n_physical_pages, int n_virtual_pages) {
    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n",
          n_physical_pages, n_virtual_pages);
    struct ipt_entry *ipt = malloc(n_physical_pages * sizeof *ipt);
    assert(ipt);

    for (int i = 0; i < n_physical_pages; i++) {
        ipt[i].virtual_page = -1;
        ipt[i].last_access_time = -1;
    }

    int virtual_page;
    for (int access_time = 0; scanf("%d", &virtual_page) == 1; access_time++) {
        assert(virtual_page >= 0 && virtual_page < n_virtual_pages);
        access_page(virtual_page, access_time, n_physical_pages, ipt);
    }
}


// if virtual_page is not in ipt, the first free page is used
// if there is no free page, the least-recently-used page is evicted
//
// a single line of output describing the page access is always printed
// the last_access_time in ipt is always updated

void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt) {
    // 1) The virtual page is already in a physical page
    for (int i = 0; i < n_physical_pages; i++) {
        if (ipt[i].virtual_page == virtual_page) {
            ipt[i].last_access_time = access_time;
            printf("Time %d: virtual page %d -> physical page %d\n", 
            access_time, virtual_page, i);
            return;
        }
    }

    // 2) The virtual page is not in a physical page, and there is free physical page
    if (!exists(virtual_page, n_physical_pages, ipt) && 
    isFree(virtual_page, n_physical_pages, ipt)) {
        int page_number = 0;
        for (int i = 0; i < n_physical_pages; i++) {
            if (ipt[i].virtual_page == -1) {
                page_number = i;
                break;
            }
        }

        ipt[page_number].last_access_time = access_time;
        ipt[page_number].virtual_page = virtual_page;

        printf("Time %d: virtual page %d loaded to physical page %d\n", 
        access_time, virtual_page, page_number);
        return;
    }

    // 3) The virtual page is not in a physical page, and there is no free physical page
    
    int least = ipt[n_physical_pages - 1].last_access_time;
    int replaced = n_physical_pages - 1;
    int replaced_virtual_page = ipt[n_physical_pages - 1].virtual_page;
    for (int i = n_physical_pages - 1; i >= 0; i--) {
        if (ipt[i].last_access_time < least) {
            replaced_virtual_page = ipt[i].virtual_page;
            least = ipt[i].last_access_time;
            replaced = i;
        } 
    }

    ipt[replaced].last_access_time = access_time;
    ipt[replaced].virtual_page = virtual_page;

    printf("Time %d: virtual page %d  - virtual page %d evicted - loaded to physical page %d\n", 
    access_time, virtual_page, replaced_virtual_page, replaced);
    return;
}

bool exists(int virtual_page, int n_physical_pages, struct ipt_entry *ipt) {
    for (int i = 0; i < n_physical_pages; i++) {
        if (ipt[i].virtual_page == virtual_page) {
            return true;
        }
        
    }
    return false;
}

bool isFree(int virtual_page, int n_physical_pages, struct ipt_entry *ipt) {
    for (int i = 0; i < n_physical_pages; i++) {
        if (ipt[i].virtual_page == -1) {
            return true;
        }
        
    }
    return false;
}
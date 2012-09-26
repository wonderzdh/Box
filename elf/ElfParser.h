#ifndef __ELF_PARSER__
#define __ELF_PARSER__

#include <vector>
#include <string>
#include <elf.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

class ElfParser {
	// private fields
	private:
		string fileName;
		FILE *felf;
		
		// .shstrtab
		unsigned char *sec_hdr_table;
		unsigned int sec_hdr_table_size;

		// .dynstr
		unsigned char *dyn_str_table;
		unsigned int dyn_str_table_size;

		// .strtab
		unsigned char *str_table;
		unsigned int str_table_size;

		Elf32_Ehdr hdr;
		vector<Elf32_Phdr> phEntries;
		vector<Elf32_Shdr> shEntries;
		vector<Elf32_Dyn> dynSecEntries;

		// content of .dynamic sections
		vector<string> needed_libraries;

		// onde procurar bibliotecas compartilhadas
		string rPath;

		// for relocations with implicit addend
		Elf32_Addr rel;				// relocation table address
		Elf32_Word relsz;			// relocation table size
		Elf32_Word relent;		// relocation entry size

		// for relocations with explicit addend
		Elf32_Addr rela;
		Elf32_Word relasz;
		Elf32_Word relaent;

		Elf32_Word pltrel;		// indicates REL or RELA for plt relocation entries
		Elf32_Addr jumprel;		// address of relocation entries associated with PLT
		Elf32_Addr pltrelsz;	// total size of relocations associated with plt entries

		Elf32_Word hash;			// address of hash symbol table
		Elf32_Word dynsym;		// address of dynamic symbol table
		Elf32_Word syment;		// size of each symbol table entry

		Elf32_Addr init;			// address of initialization stub
		Elf32_Addr fini;			// address of finalization stub

	// public methods
	public:
		ElfParser(string elfPath);

		// print the section string table
		void printSectionsHdrTable();

		// extract the section header string table content
		void extractSectionsHdrTable();

		void parseDynamicEntries();

		void printDynamicSection();

		// extract each entry of .dynamic section and store in dynSecEntries
		void extractDynamicSection(Elf32_Shdr dSec);

		// extract all string tables content
		void extractStrTabSection(Elf32_Shdr stSec);

		// iterate over Section Header entries and extract the content of each section
		// extract the content of all sections
		void extractSections();

		// extract sections header table
		void extractSecHdrTable();

		// print sections header table
		void printSecHdrTable();

		// parse program header table 
		void extractProgHdrTable();

		// return the list of program header entries
		vector<Elf32_Phdr> getProgHdrTable() { this->extractProgHdrTable(); return this->phEntries; }

		// print program header table
		void printProgHdrTable();

		char * segmentTypeName(Elf32_Word type);

		// extract elf header file
		void extractElfHeader();

		// print elf header to console
		void printElfHeader();

		// accessor methods
		vector<string> getNeededLibraries();

		string getRpath();

		void elfClose() { fclose(this->felf); };

		void read(Bit8u *content, Elf32_Off offset, Elf32_Word len);

		string getFileName();
};

#endif

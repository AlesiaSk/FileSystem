#include <iostream>
#include <fstream>
#include<conio.h>
#include<stdio.h>
#include<string>
#include<vector>

using namespace std;

int SIZE_OF_BLOCK = 256;

struct block {
	string name;
	int index;
	//данные добавить
};



struct file {
	string name;
	string type;
	char * first;
};

struct catalog {
	string name;
	vector<file> files;
	vector<catalog> catalogs;
	//еще какая-то информация о файлах должна быть
};

struct element {
	element *next;
	element *prev;
	catalog directory;
};

struct list {
	element *begin;
	element *end;
};

vector<int> indexTable;

void COPY() {

}

void RMDIR() {

}

void CD() {

}

void DIR(catalog dir) {
	// добавить проверку на то, существует ли такой каталог
	for (int i = 0; i < dir.files.size(); i++) {
		cout << dir.files[i].name << endl;
	}
	
}

void ADD_TO_DIR(file file, catalog dir) {
	dir.files.push_back(file);
}

void add_catalog(element **begin, element *beg, element **end, catalog cur_catalog) {
	element *temp = new element;
	if (*begin == NULL) {

		*begin = *end = temp;
		(*temp).prev = beg;
	}
	else {

		(*temp).prev = *end;
		(**end).next = temp;
		*end = temp;
	}
	(*temp).next = NULL;
	(*temp).directory = cur_catalog;
}

catalog DEL(catalog dir, file file) {
	for (int i = 0; i < dir.files.size(); i++) {
		if (dir.files[i].name == file.name) {
			dir.files.erase(dir.files.begin() + i);
		}
	}
	return dir;
}

catalog MD(string name) {
	//проверка на то, существует ли каталог с таким именем в текущем
	catalog new_catalog;
	(new_catalog).name = name;
	return new_catalog;
}

void MOVE(file movable, catalog cur_catalog, catalog new_catalog) {
	//возможно, нужен еще поиск этого каталога
	new_catalog.files.push_back(movable);
	for (int i = 0; i < cur_catalog.files.size(); i++) {
		if (cur_catalog.files[i].name == movable.name) {
			cur_catalog.files.erase(cur_catalog.files.begin() + i);
		}
	}
}

file CREATE_FILE(string name, string type) {
	//проверка на то, существует ли такое имя файла в текущей директории 
	file *my_file = new file;
	(*my_file).name = name;
	(*my_file).type = type;
	(*my_file).first = (char*) malloc(SIZE_OF_BLOCK);
	return *my_file;
}

void WRITE() {

}

void READ() {

}

void main() {
	string cases;
	string filename;
	string type;
	string req;
	catalog root = MD("root");
	vector<catalog> catalogs;
	catalog curr_catalog = root;
	catalog prev_catalog = root;
	//cout << "Choose 1 - Create a file; 2 - Create directory; 3 - Show files from directory; 4 - Delete file; 5 - Move file to another directory; 6 - Delete directory" << endl;
	while (true)
	{
		cout << curr_catalog.name << ">";
		cin >> cases;
		req = cases.substr(0, cases.find(" "));
		if (req == "cf") {
			cin >> cases;
			type = cases.substr(cases.length() - 3, 3);
			filename = cases.substr(cases.find(" ") + 1, cases.length() - 4);
			curr_catalog.files.push_back(CREATE_FILE(filename, type));
		}
		else if (req == "md"){
			cin >> filename;
			curr_catalog.catalogs.push_back(MD(filename));
		}
		else if (req == "dir") {
			DIR(curr_catalog);
			for (int i = 0; i < curr_catalog.catalogs.size(); i++) {
				cout << curr_catalog.catalogs[i].name << endl;
			}
		}
		else if (req == "del") {
			curr_catalog = DEL(curr_catalog, curr_catalog.files[0]);
		}
	}
	
	system("pause");
	getchar();
}
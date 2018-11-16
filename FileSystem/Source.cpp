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
	//������ ��������
};



struct file {
	string name;
	string type;
	char * first;
};

struct catalog {
	string name;
	vector<file> files;
	vector<catalog*> catalogs;
	//��� �����-�� ���������� � ������ ������ ����
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
	// �������� �������� �� ��, ���������� �� ����� �������
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

void DEL(catalog* dir, file file) {
	int curr_size = (*dir).files.size();
	for (int i = 0; i < (*dir).files.size(); i++) {
		if ((*dir).files[i].name == file.name) {
			(*dir).files.erase((*dir).files.begin() + i);
		}
	}
	if (curr_size == (*dir).files.size()) {
		cout << "�an't find this file";
	}
}

void RMDIR(catalog* dir, string deletable) {
	int curr_size = (*dir).catalogs.size();
	for (int i = 0; i < (*dir).catalogs.size(); i++) {
		catalog* deldir = (*dir).catalogs[i];
		if ((*deldir).name == deletable) {
			(*dir).catalogs.erase((*dir).catalogs.begin() + i);
		}
	}
	if (curr_size == (*dir).catalogs.size()) {
		cout << "�an't find this file";
	}
}

catalog MD(string name) {
	//�������� �� ��, ���������� �� ������� � ����� ������ � �������
	catalog new_catalog;
	(new_catalog).name = name;
	return new_catalog;
}

void MOVE(file movable, catalog cur_catalog, catalog new_catalog) {
	//��������, ����� ��� ����� ����� ��������
	new_catalog.files.push_back(movable);
	for (int i = 0; i < cur_catalog.files.size(); i++) {
		if (cur_catalog.files[i].name == movable.name) {
			cur_catalog.files.erase(cur_catalog.files.begin() + i);
		}
	}
}

file CREATE_FILE(string name, string type) {
	//�������� �� ��, ���������� �� ����� ��� ����� � ������� ���������� 
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
	catalog create;
	catalog* dir;
	catalog root = MD("root");
	vector<catalog*> path;
	catalog* curr_catalog = &root;

	path.push_back(&root);
	while (true)
	{
		for (int i = 0; i < path.size(); i++) {
			if (i == 0) {
				catalog* temp = path[i];
				cout << (*temp).name;
			}
			else {
				cout << "\\" << (*path[i]).name;
			}
		}
		cout << ">";
		cin >> cases;
		req = cases.substr(0, cases.find(" "));

		if (req == "cf") {
			cin >> cases;
			type = cases.substr(cases.length() - 3, 3);
			filename = cases.substr(cases.find(" ") + 1, cases.length() - 4);
			(*curr_catalog).files.push_back(CREATE_FILE(filename, type));
		}
		else if (req == "md") {
			cin >> filename;
			create = MD(filename);
			dir = &create;
			(*curr_catalog).catalogs.push_back(dir);
		}
		else if (req == "dir") {
			DIR(*curr_catalog);
			for (int i = 0; i < (*curr_catalog).catalogs.size(); i++) {
				catalog *temp = (*curr_catalog).catalogs[i];
				cout << (*temp).name << endl;
			}
		}
		else if (req == "del") {
			DEL(curr_catalog, (*curr_catalog).files[0]);
		}
		else if (req == "cd") {
			cin >> filename;
			for (int i = 0; i < (*curr_catalog).catalogs.size(); i++) {
				catalog *temp = (*curr_catalog).catalogs[i];
				if ((*temp).name == filename) {
					dir = (*curr_catalog).catalogs[i];
					curr_catalog = dir;
					path.push_back(curr_catalog);
				}
				else {
					cout << "Directory is not found" << endl;
				}
			}
		}
		else if (req == "back") {
			if ((*curr_catalog).name != root.name) {
				curr_catalog = path[path.size() - 2];
				path.erase(path.begin() + (path.size() - 1));
			}
		}
		else if (req == "rmdir") {
			cin >> filename;
			RMDIR(curr_catalog, filename);
		}
		else if (req == "move") {
			cin >> filename;
			RMDIR(curr_catalog, filename);
		}
		else if (req == "help") {
			cout << "md     create directory" << endl;
			cout << "cf     create file" << endl;
			cout << "cd     change directory" << endl;
			cout << "back   come back to parent directory" << endl;
			cout << "del    delete file" << endl;
			cout << "rmdir  delete directory" << endl;
			cout << endl;
		}
	}

	system("pause");
	getchar();
}
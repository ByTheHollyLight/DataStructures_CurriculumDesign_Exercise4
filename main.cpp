#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

struct course {
	char name[50];
	int hour;
	int semester;
	int indegree;
	int prev[10];
};

int cnt[9];
bool vis[100];
course cs[100];

void visit(int i, int s) {
	if (!cnt[s])return;
	if (cs[i].semester != s && cs[i].semester != 0)return;
	if (!cs[i].indegree) {
		vis[i] = true;
		cout << cs[i].name << endl;
		cnt[s]--;
	}
	else {
		for (int j = 1; j <= cs[i].indegree;j++)
			if (!vis[cs[i].prev[j]])
				visit(cs[i].prev[j], s);
		if (cnt[s] < 1) {
			cout << "Illegal arrangement" << endl;
			exit(1);
		}
		vis[i] = true;
		cout << cs[i].name << endl;
		cnt[s]--;
	}
}

void range() {
	ifstream in;
	in.open("course_inf.txt", ios::in);
	if (in.fail())
		cout << "Fail to open the course information" << endl;
	char c;
	c = in.get();
	while (c<'0' || c>'9')
		c = in.get();
	cnt[1] = c - '0';
	int remain = cnt[1];
	for (int i = 2; i <= 8; i++) {
		in >> cnt[i];
		remain += cnt[i];
	}
	int total = remain;
	while (c != 'c'&&c != EOF)
		c = in.get();
	c = in.get();
	while (c != 'c'&&c != EOF)
		c = in.get();
	while (c!=EOF) {
		remain--;
		int k = 0;
		in >> k;
		if (k > total || k < 1) {
			cout << "Illegal arrangement" << endl;
			exit(1);
		}
		in >> cs[k].name;
		in >> cs[k].hour;
		in >> cs[k].semester;
		cs[k].indegree = 0;
		c = in.get();
		if (c != '\n') {
			char tmp[5];
			in >> tmp;
			cs[k].indegree++;
			cs[k].prev[cs[k].indegree] = (tmp[1] - '0') * 10 + tmp[2] - '0';
			c = in.get();
			while (c != '\n') {
				in >> tmp;
				cs[k].indegree++;
				cs[k].prev[cs[k].indegree] = (tmp[1] - '0') * 10 + tmp[2] - '0';
				c = in.get();
			}
		}
		if (!remain)break;
		c = in.get();
	}
	memset(vis, false, sizeof(vis));
	int sem = 1, indeg = 0;
	while (sem <= 8) {
		cout << "Semester " << sem << ":" << endl;
		for (int p = 1; p <= total; p++)
			if (cs[p].semester == sem && !vis[p])
				visit(p, sem);
		for (int t = sem + 1; t <= 8; t++)
			for (int p = 1; p <= total; p++)
				if (cs[p].semester == t && !cs[p].indegree) {
					for (int j = 1; j <= cs[p].indegree; j++)
						if (!vis[cs[p].prev[j]])
							visit(cs[p].prev[j], sem);
				}
		for (int t = 0; t <= 5; t++) {
			for (int p = 1; p <= total; p++)
				if (cs[p].indegree == t && !vis[p])
					visit(p, sem);
		}
		sem++;
		cout << endl;
	}
}

int main() {
	range();
	return 0;
}
/****************************************/
/*  CourseSelectionSystem(CCS) Ver1.00  */ 
/*          Developed by sulley         */
/****************************************/
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h> 
using namespace std;

/*  
	this header file contains declarations of the mutual interfaces for students and dean.
*/
#ifndef CSS_H
#define CSS_H
struct user{
	char type;
	char username[20];
	char pw[20];
}; 
struct stu{
	char id[20];
	char name[20];
	char pw[20];
	int clas;
	int totalSelect;
};
struct course{
	int courseid;
	char coursename[50];
	int allp;
	int selectp;
	int leftp;
};
void gotoxy(int,int);
void HideCursor(int);
int checkuser(char*);
int checkDeanOrstu(char*,char*,char);
void regis(void);
void login(char);
void welcome(void);

/*
	this header file contains some declarations of operations involving students.
*/
int countclass(void);
void checkname(char*,char*);
void updateSelp(int,int);
int checkfull(int);
int checkSelCourse(char*,int);
void reviseSelCourse(char*,int,int);
void select(char*);
void drop(char*);
void viewallsel(char*);
void student(char*);

/*
	this header file contains declarations of operations involving dean.
*/
int checkcourse(char*);
int countcourse(void);
void deleteinfo(int);
void deletecourse(int);
void revisecourse(int,char*,int);
int showcourses(void);
void viewinfo(int);
void add(void);
void Delete(void);
void revise(void);
void viewcourse(void);
void dean(void);
#endif

int main()
{
	welcome();
	return 0;
}

/*
	the next two functions will be used through the program.
*/

/////////////////////////////////
// ����gotoxy(int,int):��궨λ//
/////////////////////////////////
void gotoxy(int x,int y) 
{
      COORD c;
      c.X=x-1;
      c.Y=y-1;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}   
/////////////////////////////////
// ����HideCursor(int):�������//
/////////////////////////////////
void HideCursor(int mark)
{
 CONSOLE_CURSOR_INFO cursor_info = {1, mark}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/*
	the next functions are mainly for dean.
*/

//////////////////////////////////////////////////////////
//   ����checkuser(char*):���������û����Ƿ��Ѵ���    //
//////////////////////////////////////////////////////////
int checkuser(char *s)
{
	ifstream fin("users.txt",ios_base::in);
	int isfound=0;
	string tmp;
	char t[50];
	while(getline(fin,tmp))
	{
		int p1=tmp.find(' ');
		int p2=tmp.find(' ',p1+1);
		strcpy(t,tmp.substr(p1+1,p2-p1-1).c_str());
		if(strcmp(t,s)==0){isfound=1;break;}
	}	
	if(fin.eof()) fin.clear();
	if(isfound) return 1;
	else return 0;
}
/////////////////////////////////////////////////////////////
//   ����checkDeanOrstu(char*,char *,char):����Ӧ���˺�  //
/////////////////////////////////////////////////////////////
int checkDeanOrstu(char *id,char *pw,char type)
{
	ifstream fin("users.txt",ios_base::in);
	int isfound=0;
	string tmp;
	char idt[25],pwt[25],typet;
	while(getline(fin,tmp))
	{
		typet=tmp[0];
		if(typet!=type) continue;
		int p1=tmp.find(' ');
		int p2=tmp.find(' ',p1+1);
		strcpy(idt,tmp.substr(p1+1,p2-p1-1).c_str());
		if(strcmp(idt,id)) continue;
		strcpy(pwt,tmp.substr(p2+1).c_str());
		if(strcmp(pwt,pw)) continue;
		else{isfound=1;break;}
	}
	if(fin.eof()) fin.clear();
	if(isfound) return 1;
	else return 0;
}
//////////////////////////////////////////////////////////
//   ����checkcourse(char*):�������Ŀγ��Ƿ��Ѵ���    //
//////////////////////////////////////////////////////////
int checkcourse(char *s)
{
	ifstream fin("courses.txt",ios_base::in);
	if(!fin.is_open()) return 0;
	string tmp;
	int isfound=0;
	char coursename[50];
	while(getline(fin,tmp))
	{
		int p1=tmp.find(' ');
		int p2=tmp.find(' ',p1+1);
		strcpy(coursename,tmp.substr(p1+1,p2-p1-1).c_str());
		if(strcmp(s,coursename)==0){isfound=1;break;}
		else continue;
	}
	if(isfound) return 1;
	else return 0;
}
/////////////////////////////////////////////////////
//   ����coursecount():ͳ�Ƶ�ǰ����ӵĿγ�����    //
/////////////////////////////////////////////////////
int countcourse()
{
	int cnt=0;
	string tmp;
	ifstream fin("courses.txt",ios_base::in);
	while(getline(fin,tmp)) cnt++;
	fin.close();
	fin.clear();
	return cnt;
}
//////////////////////////////////////////////
//   ����deleteinfo(int): ɾ��ѧ��ѡ����Ϣ  //
//////////////////////////////////////////////
void deleteinfo(int id)
{
	//�鿴����ѧ����Ϣ������ѡ�γ�_id_��ѧ�������޸�
	ifstream fin("students.txt",ios_base::in);
	string tmp;
	stu newstu[100];
	int cnt=0;
	int sels[100][20];
	while(getline(fin,tmp))
	{
		cnt++;
		sels[cnt][0]=0;
		int p1=tmp.find(' ');
		strcpy(newstu[cnt].id,tmp.substr(0,p1).c_str());
		int p2=tmp.find(' ',p1+1);
		strcpy(newstu[cnt].pw,tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		strcpy(newstu[cnt].name,tmp.substr(p2+1,p1-p2-1).c_str());
		p2=tmp.find(' ',p1+1);
		newstu[cnt].clas=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		newstu[cnt].totalSelect=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
		for(int i=1;i<=newstu[cnt].totalSelect;i++)
		{
			p2=tmp.find(' ',p1+1);
			int cid=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
			if(cid==id) sels[cnt][0]=1;
			sels[cnt][i]=cid;
			p1=p2;
		}
	}
	fin.close();
	fin.clear();
	ofstream fout("students.txt",ios_base::out|ios_base::trunc);
	for(int i=1;i<=cnt;i++)
	{
		fout<<newstu[i].id<<' '<<newstu[i].pw<<' '<<newstu[i].name<<' '<<newstu[i].clas<<' '
			<<newstu[i].totalSelect-sels[i][0]<<' ';
		for(int j=1;j<=newstu[i].totalSelect;j++)
		{
			if(sels[i][j]<id) fout<<sels[i][j]<<' ';
			else if(sels[i][j]>id) fout<<sels[i][j]-1<<' '; 
		}
		fout<<'\n';
	}
	fout.close();
	fout.clear();
	return;
}
////////////////////////////////////////////
//   ����deletecourse(int): ɾ����ǰ�γ�  //
////////////////////////////////////////////
void deletecourse(int id)
{
	//����Ҫɾ���Ŀγ�֮��ȫ������д�� 
	deleteinfo(id);
	course cs[20];
	ifstream fin("courses.txt",ios_base::in);
	int cnt=0;
	int idt;
	string tmp;
	while(getline(fin,tmp))
	{
		int p1=tmp.find(' ');
		idt=atoi(tmp.substr(0,p1).c_str());
		if(idt==id) continue;
		else
		{
			cnt++;
			cs[cnt].courseid=cnt;
			int p2=tmp.find(' ',p1+1);
			strcpy(cs[cnt].coursename,tmp.substr(p1+1,p2-p1-1).c_str());
			p1=tmp.find(' ',p2+1);
			cs[cnt].allp=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
			p2=tmp.find(' ',p1+1);
			cs[cnt].selectp=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
			cs[cnt].leftp=atoi(tmp.substr(p2+1).c_str());
		}
	}
	fin.close();
	fin.clear();
	ofstream fout("courses.txt",ios_base::out|ios_base::trunc);
	for(int i=1;i<=cnt;i++)
		fout<<cs[i].courseid<<' '<<cs[i].coursename<<' '
		    <<cs[i].allp<<' '<<cs[i].selectp<<' '<<cs[i].leftp<<'\n';
	fout.close();
	fout.clear();
	return;
}
//////////////////////////////////////////////////////
//   ����revisecourse(int,char*,int): �޸ĵ�ǰ�γ�  //
//////////////////////////////////////////////////////
void revisecourse(int id,char *newname,int newp)
{
	course cs[20];
	ifstream fin("courses.txt",ios_base::in);
	int idt;
	int cnt=0;
	string tmp;
	while(getline(fin,tmp))
	{
		cnt++;
		int p1=tmp.find(' ');
		idt=atoi(tmp.substr(0,p1).c_str());
		cs[cnt].courseid=idt;
		int p2=tmp.find(' ',p1+1);
		strcpy(cs[cnt].coursename,tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		cs[cnt].allp=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
		p2=tmp.find(' ',p1+1);
		cs[cnt].selectp=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
		cs[cnt].leftp=atoi(tmp.substr(p2+1).c_str());
		if(idt==id)
		{
			strcpy(cs[cnt].coursename,newname);
			cs[cnt].allp=newp;
			cs[cnt].leftp=newp-cs[cnt].selectp;
		}
	}
	fin.close();
	fin.clear();
	ofstream fout("courses.txt",ios_base::out|ios_base::trunc);
	for(int i=1;i<=cnt;i++)
		fout<<cs[i].courseid<<' '<<cs[i].coursename<<' '
		    <<cs[i].allp<<' '<<cs[i].selectp<<' '<<cs[i].leftp<<'\n';
	fout.close();
	fout.clear();
	return;
} 
/////////////////////////////////////////////////
//   ����showcourses():��ʾ��ǰ���пγ���Ϣ    //
/////////////////////////////////////////////////
int showcourses()
{
		printf("//=================================================//\n");
		printf("//   �γ���Ϣ���£���ѡ���Ӧ�γ̱�Ż��߰�0�˳�   //\n");
		printf("//=================================================//\n");
		printf("//     ---------------------------------------     //\n");
		printf("//    | �γ̱�� |     �γ���     | ��ѡ/ȫ�� |    //\n");
		printf("//     ---------------------------------------     //\n");
		int tot=countcourse();
		ifstream fin("courses.txt",ios_base::in);
		string tmp;
		for(int i=1;i<=tot;i++)
		{
			getline(fin,tmp);
			int id,allp,selp;
			char name[50];
			int p1=tmp.find(' ');
			int p2=tmp.find(' ',p1+1);
			id=atoi(tmp.substr(0,p1).c_str());
			strcpy(name,tmp.substr(p1,p2-p1).c_str());
			p1=tmp.find(' ',p2+1);
			allp=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
			p2=tmp.find(' ',p1+1);
			selp=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
			printf("//    | %-8d | %-14s | %4d/%-4d |    //\n",id,name,selp,allp);
			printf("//     ---------------------------------------     //\n");
		} 
		fin.close();
		fin.clear();
		printf("//=================================================//\n");
		printf("//                                                 //\n");  //line:8+2*tot;
		printf("//                                                 //\n");  //line:9+2*tot 
		printf("//                                                 //\n");  //line:10+2*tot
		printf("//                                                 //\n");  //line:11+2*tot
		printf("//=================================================//\n");
		return tot;
}
///////////////////////////////////////////
//   ����regis():Ϊ��ʦ��ѧ��ע���˺�    //
///////////////////////////////////////////
void regis()
{
	system("cls");
	char ch,type;
	user newid;
	stu newstu; 
	printf("//=======================================================//\n");
	printf("//      ������������ѡ��������ݣ��������û���������     //\n");
	printf("//               �û��������벻����20���ַ�              //\n");
	printf("//=======================================================//\n");
	printf("//        ѡ��������ݣ�1(��ʦ)      0(ѧ��)             //\n"); //line 5
	printf("//                                                       //\n"); //line 6
	printf("//                                                       //\n"); //line 7
	printf("//                                                       //\n"); //line 8
	printf("//                                                       //\n"); //line 9
	printf("//                                                       //\n"); //line 10
	printf("//=======================================================//\n");
	printf("//                                                       //\n"); //line 12
	printf("//                                                       //\n"); //line 13
	printf("//=======================================================//\n"); 
	HideCursor(0);
	while(1){
		ch=getch();
		if(ch=='1'||ch=='0'){newid.type=ch;break;}
	}
	type=ch;
	HideCursor(1);
	gotoxy(11,6);
	if(ch=='1')printf("���������˺ţ�");
	else printf("��������ѧ�ţ�");
	while(1)
	{
		HideCursor(1);
		scanf("%s",&newid.username);
		if(ch=='0') strcpy(newstu.id,newid.username);
		if(checkuser(newid.username)){
			gotoxy(16,7);
			printf("        �û����Ѵ��ڣ�");
			HideCursor(0);
			Sleep(1000);
			gotoxy(16,7);
			printf("                         ");
			gotoxy(25,6);
			printf("                         ");
			gotoxy(25,6);
		}
		else break;
	}
	gotoxy(11,7);
	printf("                                       ");
	gotoxy(11,7);
	printf("�����������룺"); 
	scanf("%s",&newid.pw);
	if(ch=='0') {
		strcpy(newstu.pw,newid.pw);
		gotoxy(11,8);
		printf("��������������");
		scanf("%s",newstu.name);
		gotoxy(11,9);
		printf("�������İ༶��");
		scanf("%d",&newstu.clas);
	}
	HideCursor(0);
	gotoxy(13,12);
	printf("��ȷ���������룺1(ȷ��)  0(ȡ��)");
	while(1){
		char ch=getch();
		if(ch=='1')
		{
			ofstream fout("users.txt",ios_base::app|ios_base::out);
			fout<<newid.type<<' '<<newid.username<<' '<<newid.pw<<"\n";
			if(type=='0')
			{
				fout.clear();
				fout.close();
				fout.open("students.txt",ios_base::app|ios_base::out);
				fout<<newstu.id<<' '<<newstu.pw<<' '<<newstu.name<<' '<<newstu.clas<<' '<<0<<' '<<'\n';
			}
			fout.clear();
			fout.close();
			gotoxy(25,13);
			printf("ע��ɹ���\n");
			Sleep(1500);
			return;
		}
		else if(ch=='0') {
			gotoxy(25,13);
			printf("ע��ʧ�ܣ�");
			Sleep(1500);
			return;
		} 
	}
}
////////////////////////////////
//   ����add():��ʦ��ӿγ�   //
////////////////////////////////
void add()
{
	char ch;
	course newcourse; 
	while(1)
	{
		system("cls");
		printf("//============================================//\n");
		printf("// ����ӿγ̣�����Ҫ����γ��������ѡ������ //\n");
		printf("//============================================//\n");
		printf("//      ������γ�����                        //\n");
		printf("//                                            //\n");
		printf("//                                            //\n");
		printf("//============================================//\n");
		printf("//                                            //\n");
		printf("//                                            //\n");
		printf("//============================================//\n");
		gotoxy(23,4);
		while(1)
		{
			HideCursor(1);
			scanf("%s",newcourse.coursename);
			if(checkcourse(newcourse.coursename))
			{
				gotoxy(15,5);
				printf("�γ��Ѵ��ڣ��Ƿ��˳���");
				HideCursor(0);
				gotoxy(14,6);printf("1(��������)  0(��Ҫ�˳�)");
				while(1)
				{
					ch=getch();
					if(ch=='1'||ch=='0') break;
				}
				if(ch=='0')
				{
					gotoxy(19,8);
					printf("���ʧ�ܣ�");
					Sleep(1500);
					return;
				}
				gotoxy(14,6);printf("                         ");
				gotoxy(15,5);printf("                         ");
				gotoxy(23,4); printf("                     ");
				gotoxy(23,4);
			}
			else break;
		}
		gotoxy(19,5);printf("                       ");
		gotoxy(9,5);
		printf("������γ�������"); 
		scanf("%d",&newcourse.allp);
		gotoxy(9,6); 
		HideCursor(0);
		printf("��ѡ��1(ȷ�����)   0(ȡ�����)");
		while(1){
			ch=getch();
			if(ch=='1'||ch=='0') break;
		}
		if(ch=='1')
		{
			int tot=countcourse();
			++tot;
			ofstream fout("courses.txt",ios_base::out|ios_base::app);
			fout<<tot<<' '<<newcourse.coursename<<' '<<newcourse.allp<<' '<<0<<' '<<newcourse.allp<<'\n';
			fout.close();
			fout.clear();
			HideCursor(1);
			gotoxy(11,8);printf("��ӿγ̳ɹ����Ƿ������ӣ�");
			HideCursor(0);
			gotoxy(12,9);printf("1(�������)    0(����)");
			while(1)
			{
				ch=getch();
				if(ch=='1'||ch=='0') break;
			}
			if(ch=='1') continue;
			else break;
		}
		else
		{
			gotoxy(19,8);
			printf("���ʧ�ܣ�");
			Sleep(1500);
			break;
		}
	}
	return;
}
///////////////////////////////////
//   ����Delete():��ʦɾ���γ�   //
///////////////////////////////////
void Delete()
{
	char ch[2];
	char c; 
	while(1)
	{
		int isquit=0;
		system("cls");
		HideCursor(0);
		int tot=showcourses();
		while(!isquit)
		{
			gotoxy(6,8+2*tot);
			HideCursor(1);
			printf("����������ɾ���Ŀγ̱�ţ�");scanf("%s",ch);
			int id=atoi(ch);
			if(id==0) return;
			gotoxy(6,9+2*tot);
			if(id>=1&&id<=tot)
			{
				printf("��ȷ��Ҫɾ���γ� %d ��1(ȷ��)  0(ȡ��)",id);
				HideCursor(0);
				while(1)
				{
					c=getch();
					if(c=='1')
					{
						deletecourse(id);
						gotoxy(6,10+2*tot);
						printf("ɾ���ɹ�,�Ƿ����ɾ����1(����)  0(�˳�)");
						HideCursor(0);
						while(1)
						{
							c=getch();
							if(c=='0'||c=='1') break;
						}
						if(c=='1') {isquit=1;break;}
						else return;
					}
					else if(c=='0')
					{
						gotoxy(19,10+2*tot);
						printf("ɾ���γ�ʧ�ܣ�");
						Sleep(1500);
						return;
					}
				}
			}
			else
			{
				printf("����Ŀγ̺ţ����������롣");
				gotoxy(16,8+2*tot);printf("                  ");
				continue;
			}
		}
	}
	return;	
}
///////////////////////////////////
//   ����revise():��ʦ�޸Ŀγ�   //
///////////////////////////////////
void revise()
{
	char ch[2],newname[50],c;
	int newp;
	while(1)
	{
		int isquit=0;
		system("cls");
		HideCursor(0);
		int tot=showcourses();
		while(!isquit)
		{
			gotoxy(6,8+2*tot);
			HideCursor(1);
			printf("�����������޸ĵĿγ̱�ţ�");
			scanf("%s",ch);
			int id=atoi(ch);
			if(id==0) return;
			gotoxy(6,9+2*tot);
			if(id>=1&&id<=tot)
			{
				printf("                               ");
				gotoxy(6,9+2*tot);
				printf("�������µĿγ����ƣ�");scanf("%s",newname);
				gotoxy(6,10+2*tot);
				printf("�������µ�ѡ��������");scanf("%d",&newp);
				gotoxy(6,11+2*tot);
				HideCursor(0);
				printf("��ȷ��Ҫ�޸Ŀγ� %d ��1(ȷ��)  0(ȡ��)",id); 
				while(1)
				{
					c=getch();
					if(c=='1')
					{
						revisecourse(id,newname,newp);
						gotoxy(6,11+2*tot);
						printf("                                          ");
						gotoxy(6,11+2*tot);
						printf("�޸Ŀγ̳ɹ����Ƿ�����޸ģ�1(����) 0(�˳�)");
						HideCursor(0);
						while(1)
						{
							c=getch();
							if(c=='0'||c=='1') break;
						}
						if(c=='1') {isquit=1;break;}
						else return;
					}
					else if(c=='0')
					{
						gotoxy(6,11+2*tot);
						printf("                                          ");
						gotoxy(19,11+2*tot);
						printf("�޸Ŀγ�ʧ�ܣ�");
						Sleep(1500);
						return;
					}
				}
			}
			else
			{
				printf("����Ŀγ̺ţ����������롣");
				gotoxy(16,8+2*tot);printf("                         ");
				continue;
			}
		}
	}
}
////////////////////////////////////////
//   ����viewinfo(int):�鿴�γ���Ϣ   //
////////////////////////////////////////
void viewinfo(int id)
{
	system("cls");
	ifstream fin("courses.txt",ios_base::in);
	int cnt=0;
	char coursename[50];
	string tmp;
	while(getline(fin,tmp))
	{
		int p1=tmp.find(' ');
		int idt=atoi(tmp.substr(0,p1).c_str());
		if(idt==id)
		{
			int p2=tmp.find(' ',p1+1);
			strcpy(coursename,tmp.substr(p1+1,p2-p1-1).c_str());
			break;
		}
	}
	fin.close();
	fin.clear();
	printf("//=================================================//\n");
	printf("//     %20s ��ѡ���������         //\n",coursename);
	printf("//=================================================//\n");
	printf("//      -------------------------------------      //\n");
	printf("//      |���|    ѧ��    |   ����   | �༶ |      //\n");
	printf("//      -------------------------------------      //\n");
	fin.open("students.txt",ios_base::in);
	stu newstu;
	while(getline(fin,tmp))
	{
		int p1=tmp.find(' ');
		strcpy(newstu.id,tmp.substr(0,p1).c_str());
		int p2=tmp.find(' ',p1+1);
		p1=tmp.find(' ',p2+1);
		strcpy(newstu.name,tmp.substr(p2+1,p1-p2-1).c_str());
		p2=tmp.find(' ',p1+1);
		newstu.clas=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		newstu.totalSelect=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
		if(newstu.totalSelect==0) continue;
		else
		{
			int isfound=0,q;
			for(int i=1;i<=newstu.totalSelect;i++)
			{
				q=tmp.find(' ',p1+1);
				int sel=atoi(tmp.substr(p1+1,q-p1-1).c_str());
				if(sel==id)
				{
					isfound=1;
					break;
				}
				p1=q;
			}
			if(isfound)
			{
				cnt++; 
				printf("//      |%-4d|%-12s|%-10s|%-6d|      //\n",cnt,newstu.id,newstu.name,newstu.clas);
				printf("//      -------------------------------------      //\n");				
			}
		}
	}
	printf("//=================================================//\n");
	printf("//                  �����������                   //\n");
	printf("//=================================================//\n");
	HideCursor(0);
	char ch=getch();
	return;
}
///////////////////////////////////////
//   ����viewcourse():�鿴ѡ�����   //
///////////////////////////////////////
void viewcourse()
{
	char ch[2];
	while(1)
	{
		system("cls");
		int isquit=0;
		int tot=showcourses();
		while(!isquit)
		{
			HideCursor(1);
			gotoxy(6,8+2*tot);
			printf("����������鿴�Ŀγ̵Ŀγ̱�ţ�"); scanf("%s",ch);
			int id=atoi(ch);
			if(id==0) return;
			if(id>=1&&id<=tot)  isquit=1,viewinfo(id);
			else
			{
				gotoxy(6,9+2*tot);
				printf("����Ŀγ̺ţ����������룡");
				gotoxy(6,8+2*tot);
				printf("                                   ");
				continue;
			}	
		}
	}
} 
///////////////////////////////
//   ����dean():��ʦ������   //
///////////////////////////////
void dean()
{
	while(1)
	{
		system("cls");
		char ch;
		HideCursor(0);
		printf("//=======================================//\n");
		printf("//          ��ʦ���ã���ѡ��           //\n");
		printf("//=======================================//\n");
		printf("//              1.��ӿγ�               //\n");
		printf("//              2.ɾ���γ�               //\n");
		printf("//              3.�޸Ŀγ�               //\n");
		printf("//              4.�鿴���               //\n");
		printf("//              5.����                   //\n");
		printf("//=======================================//\n");
		ch=getch();
		if(ch=='1') add();
		else if(ch=='2') Delete();
		else if(ch=='3') revise();
		else if(ch=='4') viewcourse();
		else if(ch=='5') break;
		else continue;
	}
	return;
}

/*
	the next functions are mainly for students. 
*/

///////////////////////////////////////////
//   ����countclass():ͳ�Ƶ�ǰ�༶����   //
///////////////////////////////////////////
int countclass()
{
	int cnt=0;
	ifstream fin("students.txt",ios_base::in);
	string tmp;
	while(getline(fin,tmp))
	{
		int p1=tmp.find(' ');
		int p2=tmp.find(' ',p1+1);
		p1=tmp.find(' ',p2+1);
		p2=tmp.find(' ',p1+1);
		int curClass=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
		if(curClass>cnt) cnt=curClass;
	}
	fin.close();
	fin.clear();
	return cnt;
}
/////////////////////////////////////////////////////
//   ����checkname(char*,char*):�ҵ���Ӧid������   //
/////////////////////////////////////////////////////
void checkname(char *id,char *name)
{
	ifstream fin("students.txt",ios_base::in);
	string tmp;
	int p1,p2;
	while(getline(fin,tmp))
	{
		p1=tmp.find(' ');
		if(strcmp(id,tmp.substr(0,p1).c_str())==0)
		{
			p2=tmp.find(' ',p1+1);
			p1=tmp.find(' ',p2+1);
			strcpy(name,tmp.substr(p2+1,p1-p2-1).c_str());
			fin.close();
			return;
		}
	}
}
//////////////////////////////////////////////////
//   ����updateSelp(int,int):����ѡ��������Ϣ   //
//////////////////////////////////////////////////
void updateSelp(int courseid,int type)
{
	//type==1 means a new selection while -1 a deletion of courseid
	ifstream fin("courses.txt",ios_base::in);
	course newc[20];
	int cnt=0;
	int p1,p2;
	string tmp;
	while(getline(fin,tmp))
	{
		cnt++;
		p1=tmp.find(' ');
		newc[cnt].courseid=atoi(tmp.substr(0,p1).c_str());
		p2=tmp.find(' ',p1+1);
		strcpy(newc[cnt].coursename,tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		newc[cnt].allp=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
		p2=tmp.find(' ',p1+1);
		newc[cnt].selectp=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
		newc[cnt].leftp=atoi(tmp.substr(p2+1).c_str());
		if(newc[cnt].courseid==courseid)
		{
			if(type==1)
			{
				newc[cnt].leftp--;
				newc[cnt].selectp++;
			}
			else
			{
				newc[cnt].leftp++;
				newc[cnt].selectp--;
			}
		}
	}
	fin.close();
	fin.clear();
	ofstream fout("courses.txt",ios_base::out|ios_base::trunc);
	for(int i=1;i<=cnt;i++)
		fout<<newc[i].courseid<<' '<<newc[i].coursename<<' '<<newc[i].allp<<' '<<newc[i].selectp<<' '
			<<newc[i].leftp<<'\n';
	fout.close();
	fout.clear();
	return;
}
/////////////////////////////////////////////////
//   ����checkfull(int):���ѡ�������Ƿ�����   //
/////////////////////////////////////////////////
int checkfull(int courseid)
{
	ifstream fin("courses.txt",ios_base::in) ;
	string tmp;
	int p1,p2;
	while(getline(fin,tmp))
	{
		p1=tmp.find(' ');
		if(atoi(tmp.substr(0,p1).c_str())==courseid)
		{
			p2=tmp.find(' ',p1+1);
			p1=tmp.find(' ',p2+1);
			p2=tmp.find(' ',p1+1);
			if(atoi(tmp.substr(p2+1).c_str())<=0) return 1;
			else return 0;
		}
	}
}
////////////////////////////////////////////////////
//   ����checkSelCourse(char*,int):����Ƿ�ѡ��   //
////////////////////////////////////////////////////
int checkSelCourse(char *id,int courseid)
{
	ifstream fin("students.txt",ios_base::in);
	string tmp;
	char idt[20];
	int p1,p2;
	while(getline(fin,tmp))
	{
		p1=tmp.find(' ');
		strcpy(idt,tmp.substr(0,p1).c_str());
		if(strcmp(idt,id)==0)
		{
			p2=tmp.find(' ',p1+1);
			p1=tmp.find(' ',p2+1);
			p2=tmp.find(' ',p1+1);
			p1=tmp.find(' ',p2+1);
			int seln=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
			for(int i=1;i<=seln;i++)
			{
				p2=tmp.find(' ',p1+1);
				int cid=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
				if(cid==courseid) return 1;
				p1=p2;
			}
			return 0;
		}
	}
	return 0;
}
/////////////////////////////////////////////////////////////
//   ����reviseSelCourse(char*,int,int):�޸�ѧ��ѡ����Ϣ   //
/////////////////////////////////////////////////////////////
void reviseSelCourse(char *id,int courseid,int type)
{
	updateSelp(courseid,type);
	//type==1 means new selection of courseid, while -1 means a new deletion of courseid
	ifstream fin("students.txt",ios_base::in);
	string tmp;
	stu newstu[100];
	int p1,p2,cnt=0;
	int sels[100][20];
	while(getline(fin,tmp))
	{
		cnt++;
		p1=tmp.find(' ');
		strcpy(newstu[cnt].id,tmp.substr(0,p1).c_str());
		p2=tmp.find(' ',p1+1);
		strcpy(newstu[cnt].pw,tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		strcpy(newstu[cnt].name,tmp.substr(p2+1,p1-p2-1).c_str());
		p2=tmp.find(' ',p1+1);
		newstu[cnt].clas=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		newstu[cnt].totalSelect=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
		for(int i=1;i<=newstu[cnt].totalSelect;i++)
		{
			p2=tmp.find(' ',p1+1);
			sels[cnt][i]=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
			p1=p2;
		}
		if(strcmp(id,newstu[cnt].id)==0)
		{
			if(type==1)
				sels[cnt][++newstu[cnt].totalSelect]=courseid;
			else
			{
				int i=1,j=1;
				while(i<=newstu[cnt].totalSelect)
				{
					if(sels[cnt][i]!=courseid) sels[cnt][j]=sels[cnt][i],j++,i++;
					else i++;
				}
				newstu[cnt].totalSelect--;
			}
		}
	}
	fin.close();
	fin.clear();
	ofstream fout("students.txt",ios_base::out|ios_base::trunc);
	for(int i=1;i<=cnt;i++)
	{
		fout<<newstu[i].id<<' '<<newstu[i].pw<<' '<<newstu[i].name<<' '<<newstu[i].clas<<' '
			<<newstu[i].totalSelect<<' ';
		for(int j=1;j<=newstu[i].totalSelect;j++)
			fout<<sels[i][j]<<' ';
		fout<<'\n';
	}
	fin.close();
	fin.clear();
}
////////////////////////////////////
//   ����select(char*):ѧ��ѡ��   //
////////////////////////////////////
void select(char *id)
{
	char ch;
	char s[10];
	char name[20];
	checkname(id,name);
	int courseid;
	course newc;
	while(1)
	{
		system("cls");
		printf("//=================================================//\n");
		printf("// %8sͬѧ��ã���ѡ���Ӧ�Ŀγ̻�������0�˳� //\n",name); 
		printf("//=================================================//\n");
		printf("//      --------------------------------------     //\n");
		printf("//     | �γ̱�� |     �γ���     | ʣ������ |    //\n");
		printf("//      --------------------------------------     //\n");
		int tot=countcourse();
		ifstream fin("courses.txt",ios_base::in);
		string tmp;
		for(int i=1;i<=tot;i++)
		{
			getline(fin,tmp);
			char name[50];
			int p1=tmp.find(' ');
			int p2=tmp.find(' ',p1+1);
			newc.courseid=atoi(tmp.substr(0,p1).c_str());
			strcpy(newc.coursename,tmp.substr(p1,p2-p1).c_str());
			p1=tmp.find(' ',p2+1);
			p2=tmp.find(' ',p1+1);
			newc.leftp=atoi(tmp.substr(p2+1).c_str());
			printf("//     | %-8d | %-14s | %-8d |    //\n",newc.courseid,newc.coursename,newc.leftp);
			printf("//      --------------------------------------     //\n");
		} 
		fin.close();
		fin.clear();
		printf("//=================================================//\n");
		printf("//                                                 //\n");  //line:8+2*tot;
		printf("//                                                 //\n");  //line:9+2*tot 
		printf("//                                                 //\n");  //line:10+2*tot
		printf("//                                                 //\n");  //line:11+2*tot
		printf("//=================================================//\n");
		while(1)
		{
			gotoxy(14,8+2*tot);
			printf("�������ѡ��Ŀγ̺ţ�");
			HideCursor(1);
			scanf("%s",s);
			courseid=atoi(s);
			if(courseid==0) return;
			else if(courseid>=1&&courseid<=tot)
			{
				if(checkSelCourse(id,courseid))
				{
					gotoxy(12,9+2*tot);printf("                            ");
					gotoxy(20,9+2*tot);
					printf("�����ظ�ѡ�Σ�");
					HideCursor(0);
					Sleep(1000);
					gotoxy(15,9+2*tot);
					printf("                    ");
					gotoxy(20,8+2*tot);
					printf("                       ");
					continue;
				}
				else if(checkfull(courseid))
				{
					gotoxy(12,9+2*tot);printf("                            ");
					gotoxy(20,9+2*tot);
					printf("�γ�����㣡");
					HideCursor(0);
					Sleep(1000);
					gotoxy(15,9+2*tot);
					printf("                    ");
					gotoxy(20,8+2*tot);
					printf("                       ");
					continue;
				}
				else break;
			}
			else
			{
				gotoxy(12,9+2*tot);
				printf("����Ŀγ̺ţ����������롣");
				gotoxy(20,8+2*tot);
				printf("                       ");
				continue;
			}
		}
		gotoxy(8,9+2*tot);
		printf("��ȷ��Ҫѡ��γ� %d ��1(ȷ��)  0(ȡ��)",courseid);
		HideCursor(0);
		while(1)
		{
			ch=getch();
			if(ch=='0') 
			{
				gotoxy(21,10+2*tot);
				printf("ѡ��ʧ�ܣ�");
				Sleep(1500);
				return;
			}
			else if(ch=='1') break;
		}
		HideCursor(1);
		reviseSelCourse(id,courseid,1); 
		gotoxy(14,10+2*tot);
		printf("ѡ�γɹ����Ƿ����ѡ�Σ�");
		HideCursor(0);
		gotoxy(16,11+2*tot);
		printf("1(����ѡ��) 0(�˳�)");
		while(1)
		{
			ch=getch();
			if(ch=='0') return;
			else if(ch=='1') break;
		}
	} 
	return;
}
//////////////////////////////////
//   ����drop(char*):ѧ���˿�   //
//////////////////////////////////
void drop(char *id)
{
	char name[20],cname[20];
	char ch,s[10];
	checkname(id,name);
	int courseid;
	while(1)
	{
		system("cls");
		printf("//=================================================//\n");
		printf("// %8sͬѧ��ã���ѡ���Ӧ�Ŀγ̻�������0�˳� //\n",name); 
		printf("//=================================================//\n");
		printf("//      --------------------------------------     //\n");
		printf("//     | �γ̱�� |     �γ���     | ѡ��״̬ |    //\n");
		printf("//      --------------------------------------     //\n");
		int tot=countcourse();
		ifstream fin("courses.txt",ios_base::in);
		string tmp;
		for(int i=1;i<=tot;i++)
		{
			getline(fin,tmp);
			int p1=tmp.find(' ');
			int p2=tmp.find(' ',p1+1);
			strcpy(cname,tmp.substr(p1+1,p2-p1-1).c_str());
			int isSel=checkSelCourse(id,i);
			printf("//     | %-8d | %-14s | %-8c |    //\n",i,cname,isSel?'Y':'N');
			printf("//      --------------------------------------     //\n");
		}
		fin.close();
		fin.clear();
		printf("//=================================================//\n");
		printf("//                                                 //\n");  //line:8+2*tot;
		printf("//                                                 //\n");  //line:9+2*tot 
		printf("//                                                 //\n");  //line:10+2*tot
		printf("//                                                 //\n");  //line:11+2*tot
		printf("//=================================================//\n");
		while(1)
		{
			gotoxy(14,8+2*tot);
			printf("�������ѡ��Ŀγ̺ţ�");
			HideCursor(1);
			scanf("%s",s);
			courseid=atoi(s);
			if(courseid==0) return;
			else if(courseid>=1&&courseid<=tot)
			{
				if(!checkSelCourse(id,courseid))
				{
					gotoxy(12,9+2*tot);printf("                            ");
					gotoxy(19,9+2*tot);
					printf("��ѡ����ѡ�ĿΣ�");
					HideCursor(0);
					Sleep(1000);
					gotoxy(15,9+2*tot);
					printf("                    ");
					gotoxy(20,8+2*tot);
					printf("                       ");
					continue;
				}
				else break;
			}
			else
			{
				gotoxy(12,9+2*tot);
				printf("����Ŀγ̺ţ����������롣");
				gotoxy(20,8+2*tot);
				printf("                       ");
				continue;
			}
		}
		gotoxy(8,9+2*tot);
		printf("��ȷ��Ҫ��ѡ�γ� %d ��1(ȷ��)  0(ȡ��)",courseid);
		HideCursor(0);
		while(1)
		{
			ch=getch();
			if(ch=='0') 
			{
				gotoxy(21,10+2*tot);
				printf("�˿�ʧ�ܣ�");
				Sleep(1500);
				return;
			}
			else if(ch=='1') break;
		}
		HideCursor(1);
		reviseSelCourse(id,courseid,-1); 
		gotoxy(14,10+2*tot);
		printf("�˿γɹ����Ƿ�����˿Σ�");
		HideCursor(0);
		gotoxy(16,11+2*tot);
		printf("1(�����˿�) 0(�˳�)");
		while(1)
		{
			ch=getch();
			if(ch=='0') return;
			else if(ch=='1') break;
		}
	} 
}
////////////////////////////////////////////////////
//   ����viewallsel(char*):ѧ���鿴��ǰѡ�����   //
////////////////////////////////////////////////////
void viewallsel(char *id)
{
	//1---->gather the info we need
	system("cls");
	int totalLenRow;         // totalLenRow is the length of a row of the sheet
	int info[20][20]={0};    // info[i][j] means the selection number in class _i_ for course _j_  
	int courseLen[20]={0};
	int totalSel[20]={0}; 
	int cntclass=countclass();
	int cntcourse=countcourse();
	char name[20]={0};
	char blank[200]={0},blankt[200]={0};
	char border[200]={0};
	checkname(id,name);
	ifstream finc("courses.txt",ios_base::in);
	ifstream fins("students.txt",ios_base::in);
	string tmp;
	int p1,p2,cnt=0;
	int clas,aSel,borderL;
	while(getline(finc,tmp))
	{
		cnt++;
		p1=tmp.find(' ');
		p2=tmp.find(' ',p1+1);
		courseLen[cnt]=strlen(tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		p2=tmp.find(' ',p1+1);
		totalSel[cnt]=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
	}
	finc.close();
	finc.clear();
	while(getline(fins,tmp))
	{
		p1=tmp.find(' ');
		p2=tmp.find(' ',p1+1);
		p1=tmp.find(' ',p2+1);
		p2=tmp.find(' ',p1+1);
		clas=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
		p1=tmp.find(' ',p2+1);
		aSel=atoi(tmp.substr(p2+1,p1-p2-1).c_str());
		for(int i=1;i<=aSel;i++)
		{
			p2=tmp.find(' ',p1+1);
			int cSel=atoi(tmp.substr(p1+1,p2-p1-1).c_str());
			info[clas][cSel]++;
			p1=p2;
		}
	}
	fins.close();
	fins.clear();
	totalLenRow=8+cntcourse;        //there is a '|' bwtween two courses
	for(int i=1;i<=cntcourse;i++)
		totalLenRow+=2+courseLen[i];
	for(int i=0;i<totalLenRow;i++) strcat(border,"=");
	borderL=strlen(border);
	
	//2---->show the info of _id_
	finc.open("courses.txt",ios_base::in);
	printf("//==========%s==========//\n",border);
	for(int i=0;i<borderL/2-5;i++) blank[i]=' '; blank[borderL/2-5]=0;
	for(int i=0;i<borderL-borderL/2-5;i++) blankt[i]=' '; blankt[borderL-borderL/2-5]=0;
	printf("//%s%8sͬѧ��ã����ѡ������%s//\n",blank,name,blankt); 
	printf("//==========%s==========//\n",border);
	printf("//          --------");	
	for(int i=1;i<=cntcourse;i++){
		for(int j=0;j<courseLen[i];j++) blank[j]='-';
		blank[courseLen[i]]=0;
		printf("--%s-",blank); 
	}
	printf("          //\n");
	printf("//         |  ����  |");
	for(int i=1;i<=cntcourse;i++){
		getline(finc,tmp);
		p1=tmp.find(' ');
		p2=tmp.find(' ',p1+1);
		char coursename[50];
		strcpy(coursename,tmp.substr(p1+1,p2-p1-1).c_str());
		printf(" %s |",coursename); 
	}
	finc.close();
	finc.clear();
	printf("         //\n");
	printf("//          --------");	
	for(int i=1;i<=cntcourse;i++){
		for(int j=0;j<courseLen[i];j++) blank[j]='-';
		blank[courseLen[i]]=0;
		printf("--%s-",blank); 
	}
	printf("          //\n");
	printf("//         |%-8s|",name);
	for(int i=1;i<=cntcourse;i++){
		int isSel=checkSelCourse(id,i);
		for(int j=0;j<courseLen[i]/2;j++) blank[j]=' '; blank[courseLen[i]/2]=0;
		printf(" %s%c",blank,isSel?'Y':'N');
		for(int j=0;j<courseLen[i]-courseLen[i]/2;j++)
			blank[j]=' '; blank[courseLen[i]-courseLen[i]/2]=0;
		printf("%s|",blank);
	}
	printf("         //\n");
	printf("//          --------");	
	for(int i=1;i<=cntcourse;i++){
		for(int j=0;j<courseLen[i];j++) blank[j]='-';
		blank[courseLen[i]]=0;
		printf("--%s-",blank); 
	}
	printf("          //\n");
	
	//3---->show all the selection info
	printf("//==========%s==========//\n",border);
	for(int i=0;i<borderL/2+2;i++) blank[i]=' '; blank[borderL/2+2]=0;
	for(int i=0;i<2+borderL-borderL/2;i++) blankt[i]=' '; blankt[2+borderL-borderL/2]=0;
	printf("//%s��ǰѡ����������%s//\n",blank,blankt); 
	printf("//==========%s==========//\n",border);
	
	printf("//          --------");	
	for(int i=1;i<=cntcourse;i++){
		for(int j=0;j<courseLen[i];j++) blank[j]='-';
		blank[courseLen[i]]=0;
		printf("--%s-",blank); 
	}
	printf("          //\n");
	finc.open("courses.txt",ios_base::in);
	printf("//         |  �༶  |");
	for(int i=1;i<=cntcourse;i++){
		getline(finc,tmp);
		p1=tmp.find(' ');
		p2=tmp.find(' ',p1+1);
		char coursename[50];
		strcpy(coursename,tmp.substr(p1+1,p2-p1-1).c_str());
		printf(" %s |",coursename); 
	}
	printf("         //\n");
	finc.close();
	finc.clear();
	printf("//          --------");	
	for(int i=1;i<=cntcourse;i++){
		for(int j=0;j<courseLen[i];j++) blank[j]='-';
		blank[courseLen[i]]=0;
		printf("--%s-",blank); 
	}
	printf("          //\n");
	
	for(int i=1;i<=cntclass;i++)
	{
		printf("//         |  %2d��  |",i);
		for(int j=1;j<=cntcourse;j++){
			for(int k=0;k<courseLen[j]/2;k++) blank[k]=' '; blank[courseLen[j]/2]=0;
			printf("%s%2d",blank,info[i][j]);
			for(int k=0;k<courseLen[j]-courseLen[j]/2;k++)
				blank[k]=' '; blank[courseLen[j]-courseLen[j]/2]=0;
			printf("%s|",blank);
		}
		printf("         //\n");
		printf("//          --------");	
		for(int j=1;j<=cntcourse;j++){
			for(int k=0;k<courseLen[j];k++) blank[k]='-';
			blank[courseLen[j]]=0;
			printf("--%s-",blank); 
		}
		printf("          //\n");
	}
	
	printf("//         | ������ |");
	for(int i=1;i<=cntcourse;i++){
		for(int j=0;j<courseLen[i]/2;j++) blank[j]=' '; blank[courseLen[i]/2]=0;
		printf("%s%2d",blank,totalSel[i]);
		for(int j=0;j<courseLen[i]-courseLen[i]/2;j++)
			blank[j]=' '; blank[courseLen[i]-courseLen[i]/2]=0;
		printf("%s|",blank);
	}
	printf("         //\n");
	printf("//          --------");	
	for(int i=1;i<=cntcourse;i++){
		for(int j=0;j<courseLen[i];j++) blank[j]='-';
		blank[courseLen[i]]=0;
		printf("--%s-",blank); 
	}
	printf("          //\n");
	
	//4---->press any key to quit
	printf("//==========%s==========//\n",border);
	for(int i=0;i<borderL/2+4;i++) blank[i]=' ';
	blank[borderL/2+4]=0;
	for(int i=0;i<4+borderL-borderL/2;i++) blankt[i]=' ';
	blankt[4+borderL-borderL/2]=0;
	printf("//%s��������˳�%s//\n",blank,blankt);
	printf("//==========%s==========//\n",border);
	HideCursor(0);
	char ch=getch();
}
//////////////////////////////////
//   ����student():ѧ��������   //
//////////////////////////////////
void student(char *id)
{
	while(1)
	{
		system("cls");
		char ch;
		HideCursor(0);
		char name[50];
		checkname(id,name);
		printf("//=======================================//\n");
		printf("//       %8sͬѧ���ã���ѡ��      //\n",name);
		printf("//=======================================//\n");
		printf("//               1.ѡ��                  //\n");
		printf("//               2.�˿�                  //\n");
		printf("//               3.�鿴                  //\n");
		printf("//               4.����                  //\n");
		printf("//=======================================//\n");
		ch=getch();
		if(ch=='1') select(id);
		else if(ch=='2') drop(id);
		else if(ch=='3') viewallsel(id);
		else if(ch=='4') break;
		else continue; 
	}
	return;
}


//////////////////////////////////////////////
//   ����login(char):Ϊ��ʦ��ѧ����½�˺�   //
//////////////////////////////////////////////
void login(char type)
{
	system("cls"); 
	char id[20],pw[30];
	printf("//=======================================//\n");
	printf("//    �û����ã������������˺ź�����     //\n");
	printf("//=======================================//\n");
	printf("//        ���������˺ţ�                 //\n");
	printf("//        �����������룺                 //\n");
	printf("//=======================================//\n");
	printf("//                                       //\n");
	printf("//                                       //\n");
	printf("//=======================================//\n");
	while(1)
	{
		HideCursor(1);
		gotoxy(25,4);scanf("%s",id);
		gotoxy(25,5);scanf("%s",pw);
		if(checkDeanOrstu(id,pw,type)) break;
		else{
			gotoxy(4,7);
			printf("�˺Ų����ڻ��˺����벻ƥ�䣬�Ƿ��˳���");
			gotoxy(10,8);
			printf("1(ѡ���˳�)  0(��������)");
			HideCursor(0);
			char ch=getch();
			if(ch=='1') return;
			else{
				gotoxy(10,8);printf("                         ");
				gotoxy(3,7);printf("                                       ");
				gotoxy(25,5);printf("               ");
				gotoxy(25,4);printf("               ");
			} 
		}
	}
	gotoxy(10,8);
	printf("��½�ɹ�����������ҳ�棡");
	HideCursor(0);
	Sleep(1500);
	if(type=='1') dean();
	else student(id);
	return;
}
///////////////////////////////
//   ����welcome():������    //
///////////////////////////////
void welcome(void)
{
	char ch;
	while(1)
	{
		system("cls");
		HideCursor(0);
		printf("//=======================================//\n");
		printf("//            ��ӭʹ�ñ�ϵͳ             //\n");
		printf("//                ��ѡ��                 //\n");
		printf("//=======================================//\n");
		printf("//                1.ע��                 //\n");
		printf("//                2.����                 //\n");
		printf("//                3.ѧ��                 //\n");
		printf("//                4.�˳�                 //\n");
		printf("//=======================================//\n");
		printf("//             ϵͳʹ��˵��              //\n");
		printf("// 1.��ϵͳ�ṩע��,����������ʾ���� //\n");
		printf("// 2.����ʦͬѧ�����Ӧҳ����ٵ�½      //\n");
		printf("// 3.Ŀǰ��֧�ּ��̲���                  //\n");
		printf("// 4.��ϸ˵����ο�'CSSʵ�鱨��.pdf'     //\n");
		printf("//   created by sulley   version:1.00    //\n");
		printf("//=======================================//\n");
		ch=getch();
		if(ch=='1') regis();
		else if(ch=='2') login('1');
		else if(ch=='3') login('0');
		else if(ch=='4') break;
	}
	return;
}

/* 
 * student.cpp 学生成绩管理系统 
 * 数据结构:双向链表
 * 功能:增,删,存,加密,遍历,排序
 * 注意:数据输入的合法性
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>//windows下system调用函数原型Linux下则为<unistd.h>
using namespace std;
typedef struct student{
	int Id;//学号
	char name[64];//名字
	float c_score;//c成绩
	float cpp_score;//cpp成绩
	float linux_score;//linux成绩
}student_t;

student_t *student_read;
student_t *student;

char passwds[64];
char quit;

class List{
public:
	List(void):m_head(NULL),m_tail(NULL){}
	~List(void){
		for(Node *node=m_head;node;node=m_head){
			m_head = node->m_next;
			delete node;
		}	
	}
	//添加节点
	void append(student_t *student){
		m_tail = new Node(student,m_tail);
		if(m_tail->m_prev)
			m_tail->m_prev->m_next=m_tail;
		else
			m_head=m_tail;	
	}
	//读取链表信息
	void forword(void){
		for(Node *node=m_head;node;node=node->m_next){
			cout << "学号:" << node->m_student->Id << "\t" << "名字:" 	\
				 << node->m_student->name << "\t" << "C_Score:"		    \
				 << node->m_student->c_score << "\t" << "Cpp_Score:" 	\
				 << node->m_student->cpp_score << "\t" 					\
				 << "linux_score:" << node->m_student->linux_score << endl;
		}
	}
	//删除学生节点
	void del_stu(int num){
		for(Node *find=m_head;find;find=find->m_next){
			if(num==find->m_student->Id){
				if(find->m_prev)
					find->m_prev->m_next=find->m_next;
				else
					m_head=find->m_next;
				if(find->m_next)
					find->m_next->m_prev=find->m_prev;
				else
					m_tail=find->m_prev;
				delete find;
			}
		}
	}
	//节点排序
	void stu_sort(void){
		for(Node *find=m_head;find;find=find->m_next){
			if(find->m_next){
				if(find->m_student->Id > find->m_next->m_student->Id){
				student_t *temp = find->m_student;
			        find->m_student = find->m_next->m_student;
				find->m_next->m_student = temp;	
				}
			}
		}
	}
	//密码存入文件
	void save_pass(void){
		ofstream stu("stu.dat",ios::binary|ios::out);
		if(!stu)return;
		cout << "输入存储密码:";
		cin >> passwds;
		stu.write(passwds,sizeof(passwds));
		stu.close();
	}
	//链表存入文件
	void save_stu(List *list){
		ofstream stu("stu.dat",ios::binary|ios::out|ios::app);
		if(!stu)return;
		for(Node *find=m_head;find;find=find->m_next){
			stu.write((char*)find->m_student,sizeof(student_t));
		}
		stu.close();
	}
	//读取密码,并验证
	int read_passwd(void){
		ifstream stu("stu.dat",ios::binary|ios::in);
		if(!stu)return -1;
		//文件不为空则读取
		if(!(stu.peek()==EOF)){
			char yanzheng[64];
			stu.read(yanzheng,sizeof(passwds));
			if(!(strcmp(passwds,yanzheng)==0)){
					return -2;
			}
		}
		stu.close();
		return 1;
	}
	//读取文件信息,并将信息添加到链表中
	int read_stu(List *list){
		ifstream stu("stu.dat",ios::binary|ios::in);
		if(!stu)return -1;
		//文件不为空则读取
		if(!(stu.peek()==EOF)){
			stu.seekg(64);
			while(1){
				student_read = new student_t;
				stu.read((char*)student_read,sizeof(student_t));
				if(stu.eof())
					break;
				list->append((student_t*)student_read);
			}
			return 1;
		}else
			return -1;
		stu.close();
		student_read=NULL;
	}
	void hefa_Id(void){
		cout << "输入您的学号:";
		cin.sync();
		cin >> student->Id;
		while(1){
			//判断学号输入的合法性
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "输入不合法,请重新输入" << endl;
			else
				break;
			cin.clear();//清空输入流缓冲区标志位
			cin.sync();//清空输入流缓区
			cin >> student->Id;
		}
	}
	void hefa_Name(void){
		while(1){
			//判断名字输入的合法性
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "输入不合法,请重新输入" << endl;
			else
				break;
			cin.clear();//清空输入流缓冲区标志位
			cin.sync();//清空输入流缓区
			cin >> student->name;
		}
	}
	void hefa_C(void){
		while(1){
			//判断C分数输入的合法性
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "输入不合法,请重新输入" << endl;
			else
				break;
			cin.clear();//清空输入流缓冲区标志位
			cin.sync();//清空输入流缓区
			cin >> student->c_score;
		}
	}
	void hefa_Cpp(void){
		while(1){
			//判断Cpp分数输入的合法性
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "输入不合法,请重新输入" << endl;
			else
				break;
			cin.clear();//清空输入流缓冲区标志位
			cin.sync();//清空输入流缓区
			cin >> student->cpp_score;
		}
	}
	void hefa_Linux(void){
		while(1){
			//判断Linux分数输入的合法性
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "输入不合法,请重新输入" << endl;
			else
				break;
			cin.clear();//清空输入流缓冲区标志位
			cin.sync();//清空输入流缓区
			cin >> student->linux_score;
		}
	}
	void hefa_quit(void){
		while(1){
			//判断Linux分数输入的合法性
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "输入不合法,请重新输入" << endl;
			else
				break;
			cin.clear();//清空输入流缓冲区标志位
			cin.sync();//清空输入流缓区
			cin >> quit;
		}
	}
private:
	class Node{
	public:
		Node(student_t *student=NULL,Node *prev=NULL,Node *next=NULL):	\
				m_student(student),m_prev(prev),m_next(next){}
		~Node(void){
			delete m_student;
			m_student=NULL;
		}
		student_t *m_student;
		Node *m_prev;
		Node *m_next; 	
	};
	Node *m_head;
	Node *m_tail;
};
int main(void){
	int err_3=0,okk;
	List students;
	int oke = students.read_stu(&students);
	if(oke==-1)
		cout << "文件中没有数据!" << endl;
	else{
		cout << "警告!密码输错3次,数据将被清空!!!" << endl;
err_pass:
		cout << "请输入密码:";
		cin >> passwds;
		err_3++;
		okk = students.read_passwd();
		if(okk==-2){
			if(err_3==3){
				cout << "输入错误总计3次,文件内数据将被清空" << endl;	
				students.~List();
				students.save_stu(&students);
			}else{
				cout << "密码错误,请重新输入,你已输错"<< err_3 << "次"	\
					 << "还有"<< 3-err_3 << "次机会!" << endl;
				goto err_pass;
			}
		}
		students.forword();
	}
	cout << "学生成绩管理系统" << endl;	
	while(1){	
		system("cls");
		cout << "###################	请输入您的选项	#######################" << endl;	
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;	
		cout << "  	    [ a:添加一条记录 d:删除一条记录 t: 清空数据 ]       "    << endl;	
		cout << "  	    [         u:排序 s:存入文件 q:退出          ]       "    << endl;	
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;	
		cout << "###################	请输入您的选项	#######################" << endl;	
		students.forword();
		cin >> quit;
		students.hefa_quit();
		if(quit=='a'||quit=='d'||quit=='s'||quit=='q'||quit=='u'||quit=='t'){			
			switch(quit){
				/*手动录入学生信息*/
				case 'a':
					student = new student_t;
					//判断学号输入的合法性
					students.hefa_Id();

					cout << "输入您的名字:";
					cin >> student->name;
					//判断名字输入的合法性
					students.hefa_Name();

					cout << "输入您的C语言成绩:";
					cin >> student->c_score;
					//判断分数输入的合法性
					students.hefa_C();

					cout << "输入您的C++语言成绩:";
					cin >> student->cpp_score;
					students.hefa_Cpp();

					cout << "输入您的Linux成绩:";
					cin >> student->linux_score;
					students.hefa_Linux();

					students.append(student);
					break;
				/*通过学生学号删除学生记录*/
				case 'd':
					cout << "输入您要删除记录的学生的学号:";
					int id;
					cin >> id;
					students.del_stu(id);
					break;
				case 't':
					cout << "清空数据中..." << endl;
					students.~List();
					cout << "清空数据完毕!" << endl;
					break;
				case 'u':
					cout << "排序中..." << endl;
					students.stu_sort();
					cout << "排序完毕!" << endl;
					break;
				case 's':
					students.save_pass();
					cout << "正在存入..." << endl;
					students.save_stu(&students);
					cout << "存入完毕!" << endl;
					break;
				case 'q':
					students.save_pass();
					students.save_stu(&students);
					goto exit_stu;
			}
			students.forword();
			system("pause");
		}else{
			cout << "输入错误!" << endl;
			continue;
		}
	}
exit_stu:
	return 0;	
}

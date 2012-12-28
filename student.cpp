/* 
 * student.cpp ѧ���ɼ�����ϵͳ 
 * ���ݽṹ:˫������
 * ����:��,ɾ,��,����,����,����
 * ע��:��������ĺϷ���
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>//windows��system���ú���ԭ��Linux����Ϊ<unistd.h>
using namespace std;
typedef struct student{
	int Id;//ѧ��
	char name[64];//����
	float c_score;//c�ɼ�
	float cpp_score;//cpp�ɼ�
	float linux_score;//linux�ɼ�
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
	//��ӽڵ�
	void append(student_t *student){
		m_tail = new Node(student,m_tail);
		if(m_tail->m_prev)
			m_tail->m_prev->m_next=m_tail;
		else
			m_head=m_tail;	
	}
	//��ȡ������Ϣ
	void forword(void){
		for(Node *node=m_head;node;node=node->m_next){
			cout << "ѧ��:" << node->m_student->Id << "\t" << "����:" 	\
				 << node->m_student->name << "\t" << "C_Score:"		    \
				 << node->m_student->c_score << "\t" << "Cpp_Score:" 	\
				 << node->m_student->cpp_score << "\t" 					\
				 << "linux_score:" << node->m_student->linux_score << endl;
		}
	}
	//ɾ��ѧ���ڵ�
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
	//�ڵ�����
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
	//��������ļ�
	void save_pass(void){
		ofstream stu("stu.dat",ios::binary|ios::out);
		if(!stu)return;
		cout << "����洢����:";
		cin >> passwds;
		stu.write(passwds,sizeof(passwds));
		stu.close();
	}
	//��������ļ�
	void save_stu(List *list){
		ofstream stu("stu.dat",ios::binary|ios::out|ios::app);
		if(!stu)return;
		for(Node *find=m_head;find;find=find->m_next){
			stu.write((char*)find->m_student,sizeof(student_t));
		}
		stu.close();
	}
	//��ȡ����,����֤
	int read_passwd(void){
		ifstream stu("stu.dat",ios::binary|ios::in);
		if(!stu)return -1;
		//�ļ���Ϊ�����ȡ
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
	//��ȡ�ļ���Ϣ,������Ϣ��ӵ�������
	int read_stu(List *list){
		ifstream stu("stu.dat",ios::binary|ios::in);
		if(!stu)return -1;
		//�ļ���Ϊ�����ȡ
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
		cout << "��������ѧ��:";
		cin.sync();
		cin >> student->Id;
		while(1){
			//�ж�ѧ������ĺϷ���
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "���벻�Ϸ�,����������" << endl;
			else
				break;
			cin.clear();//�����������������־λ
			cin.sync();//�������������
			cin >> student->Id;
		}
	}
	void hefa_Name(void){
		while(1){
			//�ж���������ĺϷ���
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "���벻�Ϸ�,����������" << endl;
			else
				break;
			cin.clear();//�����������������־λ
			cin.sync();//�������������
			cin >> student->name;
		}
	}
	void hefa_C(void){
		while(1){
			//�ж�C��������ĺϷ���
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "���벻�Ϸ�,����������" << endl;
			else
				break;
			cin.clear();//�����������������־λ
			cin.sync();//�������������
			cin >> student->c_score;
		}
	}
	void hefa_Cpp(void){
		while(1){
			//�ж�Cpp��������ĺϷ���
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "���벻�Ϸ�,����������" << endl;
			else
				break;
			cin.clear();//�����������������־λ
			cin.sync();//�������������
			cin >> student->cpp_score;
		}
	}
	void hefa_Linux(void){
		while(1){
			//�ж�Linux��������ĺϷ���
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "���벻�Ϸ�,����������" << endl;
			else
				break;
			cin.clear();//�����������������־λ
			cin.sync();//�������������
			cin >> student->linux_score;
		}
	}
	void hefa_quit(void){
		while(1){
			//�ж�Linux��������ĺϷ���
			if(cin.fail()||cin.bad()||cin.get()!='\n')
				cout << "���벻�Ϸ�,����������" << endl;
			else
				break;
			cin.clear();//�����������������־λ
			cin.sync();//�������������
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
		cout << "�ļ���û������!" << endl;
	else{
		cout << "����!�������3��,���ݽ������!!!" << endl;
err_pass:
		cout << "����������:";
		cin >> passwds;
		err_3++;
		okk = students.read_passwd();
		if(okk==-2){
			if(err_3==3){
				cout << "��������ܼ�3��,�ļ������ݽ������" << endl;	
				students.~List();
				students.save_stu(&students);
			}else{
				cout << "�������,����������,�������"<< err_3 << "��"	\
					 << "����"<< 3-err_3 << "�λ���!" << endl;
				goto err_pass;
			}
		}
		students.forword();
	}
	cout << "ѧ���ɼ�����ϵͳ" << endl;	
	while(1){	
		system("cls");
		cout << "###################	����������ѡ��	#######################" << endl;	
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;	
		cout << "  	    [ a:���һ����¼ d:ɾ��һ����¼ t: ������� ]       "    << endl;	
		cout << "  	    [         u:���� s:�����ļ� q:�˳�          ]       "    << endl;	
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;	
		cout << "###################	����������ѡ��	#######################" << endl;	
		students.forword();
		cin >> quit;
		students.hefa_quit();
		if(quit=='a'||quit=='d'||quit=='s'||quit=='q'||quit=='u'||quit=='t'){			
			switch(quit){
				/*�ֶ�¼��ѧ����Ϣ*/
				case 'a':
					student = new student_t;
					//�ж�ѧ������ĺϷ���
					students.hefa_Id();

					cout << "������������:";
					cin >> student->name;
					//�ж���������ĺϷ���
					students.hefa_Name();

					cout << "��������C���Գɼ�:";
					cin >> student->c_score;
					//�жϷ�������ĺϷ���
					students.hefa_C();

					cout << "��������C++���Գɼ�:";
					cin >> student->cpp_score;
					students.hefa_Cpp();

					cout << "��������Linux�ɼ�:";
					cin >> student->linux_score;
					students.hefa_Linux();

					students.append(student);
					break;
				/*ͨ��ѧ��ѧ��ɾ��ѧ����¼*/
				case 'd':
					cout << "������Ҫɾ����¼��ѧ����ѧ��:";
					int id;
					cin >> id;
					students.del_stu(id);
					break;
				case 't':
					cout << "���������..." << endl;
					students.~List();
					cout << "����������!" << endl;
					break;
				case 'u':
					cout << "������..." << endl;
					students.stu_sort();
					cout << "�������!" << endl;
					break;
				case 's':
					students.save_pass();
					cout << "���ڴ���..." << endl;
					students.save_stu(&students);
					cout << "�������!" << endl;
					break;
				case 'q':
					students.save_pass();
					students.save_stu(&students);
					goto exit_stu;
			}
			students.forword();
			system("pause");
		}else{
			cout << "�������!" << endl;
			continue;
		}
	}
exit_stu:
	return 0;	
}

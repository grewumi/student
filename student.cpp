#include <iostream>
#include <fstream>
using namespace std;
typedef struct student{
	int Id;//ѧ��
	char name[64];//����
	float c_score;//c�ɼ�
	float cpp_score;//cpp�ɼ�
	float linux_score;//linux�ɼ�
}student_t;
student_t *student_read;
char passwds[64];
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
	void save_pass(char *passwd){
		ofstream stu("stu.dat",ios::binary|ios::out);
		if(!stu)return;
		cout << "д���ļ�������:" << passwd << endl;
		stu.write(passwd,sizeof(passwds));
		stu.close();
	}
	//��������ļ�
	void save_stu(List *list){
		ofstream stu("stu.dat",ios::binary|ios::out);
		if(!stu)return;
		stu.seekp(64);
		for(Node *find=m_head;find;find=find->m_next){
			stu.write((char*)find->m_student,sizeof(student_t));
		}
		stu.close();
	}
	//��ȡ����,����֤
	int read_passwd(char *passwd){
		ifstream stu("stu.dat",ios::binary|ios::in);
		if(!stu)return -1;
		//�ļ���Ϊ�����ȡ
		if(!(stu.peek()==EOF)){
			char yanzheng[64];
			stu.read(yanzheng,sizeof(passwds));
			cout << "�����ļ�������:" << yanzheng << endl;
			if(!(strcmp(passwd,yanzheng)==0)){
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
	student_t *student;
	int oke = students.read_stu(&students);
	if(oke==-1)
		cout << "�ļ���û������!" << endl;
	else{
		cout << "����!�������3��,���ݽ������!!!" << endl;
err_pass:
		cout << "����������:";
		cin >> passwds;
		err_3++;
		okk = students.read_passwd(passwds);
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
	char quit;
	cout << "ѧ���ɼ�����ϵͳ" << endl;	
	while(1){	
		cout << "����������ѡ��:[ a:���һ����¼ d:ɾ��һ����¼ t: ������� u:���� s:�����ļ� q:�˳� ]" << endl;	
		cin >> quit;
		if(quit=='a'||quit=='d'||quit=='s'||quit=='q'||quit=='u'||quit=='t'){			
			switch(quit){
				/*�ֶ�¼��ѧ����Ϣ*/
				case 'a':
					student = new student_t;
					cout << "��������ѧ��:";
					cin >> student->Id;
					//�ж�ѧ������ĺϷ���
					cout << "������������:";
					cin >> student->name;
					//�ж���������ĺϷ���
					cout << "��������C���Գɼ�:";
					cin >> student->c_score;
					//�жϷ�������ĺϷ���
					cout << "��������C++���Գɼ�:";
					cin >> student->cpp_score;
					cout << "��������Linux�ɼ�:";
					cin >> student->linux_score;
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
					cout << "����洢����:";
					cin >> passwds;
					students.save_pass(passwds);
					cout << "���ڴ���..." << endl;
					students.save_stu(&students);
					cout << "�������!" << endl;
					break;
				case 'q':
					goto exit_stu;
			}
			students.forword();
		}else{
			cout << "�������!" << endl;
			continue;
		}
	}
exit_stu:
	return 0;	
}

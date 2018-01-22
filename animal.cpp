#include <string>
#include <iostream>
#include <fstream>

#define DATAFILE_QUESTIONS "questions.txt"
#define DATAFILE_ANSWERS "answers.txt"

using namespace std;



class Node
{
public:
	void process();
	void ask(); // The AI asks the user a question from the database.
	void guess(); // The AI reaches a conclusion and makes a guess to the user.
	void request(); // The AI did not guess correctly and request the user to add information to the database.

	// Constructor
	Node(string question_init, string answer_init, Node * yes_init, Node * no_init);
	// Destructor (unused)
	~Node();

	string question;
	string answer;
	Node * yes;
	Node * no;
};


// Constructor
Node::Node(string question_init, string answer_init, Node * yes_init, Node * no_init): 
question(question_init), answer(answer_init), yes(yes_init), no(no_init) {}


void
Node::process()
{
	if (question == "None")
	{
		guess();
	}
	else
	{
		ask();
	}
}

void
Node::ask()
{
	cout << question << endl;
	cout << "Please input \"yes\" or \"no\"." << endl;
	string response;
	getline(cin, response);
	while ((response != "yes") && (response != "no"))
	{
		cout << "I did not recognize it!" << endl;
		cout << "Please input \"yes\" or \"no\"." << endl;
		getline(cin, response);
	}
	if (response == "yes")
	{
		yes->process();
	}
	else
	{
		no->process();
	}
}

void
Node::guess()
{
	cout << "Is it " << answer << "?" << endl;
	string response;
	getline(cin, response);
	while ((response != "yes") && (response != "no"))
	{
		cout << "I did not recognize it!" << endl;
		cout << "Please input \"yes\" or \"no\"." << endl;
		getline(cin, response);
	}
	if (response == "yes")
	{
		cout << "I knew it!" << endl;
	}
	else
	{
		cout << "Now I give up." << endl;
		request();
	}
}

void
Node::request()
{
	cout << "What is it?" << endl;
	string user_answer;
	string user_question;
	string response;
	getline(cin, user_answer);
	cout << "I see. How do I tell it apart from " << answer << "?" << endl;
	cout << "Please give a question with a yes or no answer." << endl;
	getline(cin, user_question);
	while (user_question.empty())
	{
		cout << "Question cannot be empty! Please enter the question again." << endl;
		getline(cin, user_question);
	}
	cout << "OK. " << user_answer << ". " << user_question << endl;
	getline(cin, response);
	while ((response != "yes") && (response != "no"))
	{
		cout << "I did not recognize it!" << endl;
		cout << "Please input \"yes\" or \"no\"." << endl;
		getline(cin, response);
	}

	// Use the new information to construct new childrens in the trees
	question = user_question;
	if (response == "yes")
	{
		yes = new Node("None", user_answer, nullptr, nullptr);
		no = new Node("None", answer, nullptr, nullptr);
		answer = "None";
	}
	else
	{
		yes = new Node("None", answer, nullptr, nullptr);
		no = new Node("None", user_answer, nullptr, nullptr);
		answer = "None";		
	}
	cout << "Thank you. I have learned a lot about " << user_answer << "." << endl;
}


static Node * root_initializer()
{
	Node * yes_node = new Node("None", "dove", nullptr, nullptr);
	Node * no_node = new Node("None", "dog", nullptr, nullptr);
	Node * root = new Node("Does it fly?", "None", yes_node, no_node);
	return root;
}


// My "unique" contribution
// Save the animal information to file
// https://articles.leetcode.com/serializationdeserialization-of-binary/
static void write_binary_tree(Node *node, ofstream &out_question, ofstream &out_answer) 
{
	if (node == nullptr) 
	{
		out_question << "#" << "\n";
		out_answer << "#" << "\n";
	}
	else
	{
		out_question << node->question << "\n";
		out_answer << node->answer << "\n";
		write_binary_tree(node->yes, out_question, out_answer);
		write_binary_tree(node->no, out_question, out_answer);
	}
}

static Node * read_binary_tree(ifstream &in_question, ifstream &in_answer)
{
	string question;
	string answer;

	if (getline(in_question, question) && getline(in_answer, answer))
	{
		if ((question != "#") && (answer != "#"))
		{
			Node * node = new Node(question, answer, nullptr, nullptr);
			node->yes = read_binary_tree(in_question, in_answer);
			node->no = read_binary_tree(in_question, in_answer);
			return node;
		}
	}

	return nullptr;

}

static void save_binary_tree(Node *node, string questions_filename, string answers_filename)
{
	ofstream fhand_questions;
	ofstream fhand_answers;
	fhand_questions.open(questions_filename);
	fhand_answers.open(answers_filename);

	if (fhand_questions.is_open() && fhand_answers.is_open())
	{
		write_binary_tree(node, fhand_questions, fhand_answers);
	}

	fhand_questions.close();
	fhand_answers.close();
}

static Node * load_binary_tree(string questions_filename, string answers_filename)
{
	ifstream fhand_questions;
	ifstream fhand_answers;
	fhand_questions.open(questions_filename);
	fhand_answers.open(answers_filename);

	if (fhand_questions.is_open() && fhand_answers.is_open())
	{
		Node * root = read_binary_tree(fhand_questions, fhand_answers);
		fhand_questions.close();
		fhand_answers.close();
		return root;
	}

	return nullptr;
}



int main()
{
	cout << "Welcome to Animal World!" << endl;
	cout << "Loading Data..." << endl;

	Node * root;
	ifstream fhand_questions (DATAFILE_QUESTIONS);
	ifstream fhand_answers (DATAFILE_ANSWERS);
	if (fhand_questions.is_open() && fhand_answers.is_open())
	{
		cout << "Dataset Found!" << endl;
		root = load_binary_tree(DATAFILE_QUESTIONS, DATAFILE_ANSWERS);
		cout << "Loading Complete." << endl;
	}
	else
	{
		cout << "Dataset Not Found!" << endl;
		root = root_initializer();
		cout << "Start from Empty Database." << endl;
	}

	while (true)
	{
		cout << endl;
		cout << "Please think of an animial in your mind." << endl;
		root->process();
		save_binary_tree(root, DATAFILE_QUESTIONS, DATAFILE_ANSWERS);
		cout << "Let's play again!" << endl;
	}
}





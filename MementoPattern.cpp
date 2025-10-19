#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class ResumeEditor{
    private:
    string name;
    string education;
    string experience;
    vector<string> skills;

    public:
      void setName(const string& n){
        name = n;
      }

      void setEducation(const string& edu){
        education = edu;
      }

        void setExperience(const string& exp){
            experience = exp;
        }

        void setSkills(const vector<string>& sk){
            skills = sk;
        }

        void printResume(){
            cout << "Resume:" << endl;
            cout << "Name: " << name << endl;
            cout << "Education: " << education << endl;
            cout << "Experience: " << experience << endl;
            cout << "Skills: ";
            for(const auto& skill : skills){
                cout << skill << " ";
            }
            cout << endl;
        }

        class Memento{
            private:
            string name;
            string education;
            string experience;
            vector<string> skills;

            public:
            Memento(const string& n, const string& edu, const string& exp, const vector<string>& sk)
            : name(n), education(edu), experience(exp), skills(sk) {}

            friend class ResumeEditor;
        };

        Memento* save(){
            return new Memento(name, education, experience, skills);
        }
        void restore(Memento* memento){
            name = memento->name;
            education = memento->education;
            experience = memento->experience;
            skills = memento->skills;
        }
};

class ResumeHistory{
    private:
    stack<ResumeEditor::Memento*> history;
    public:
    void save(ResumeEditor& editor){
        history.push(editor.save());
    }

    void undo(ResumeEditor& editor){
        if(!history.empty()){
            ResumeEditor::Memento* memento = history.top();
            history.pop();
            editor.restore(memento);
            delete memento;
        }
        else{
            cout << "No previous state to restore." << endl;
        }
    }
    
};

int main() {
    ResumeEditor editor;
    ResumeHistory history;

    editor.setName("John Doe");
    editor.setEducation("B.Sc. in Computer Science");
    editor.setExperience("2 years at TechCorp");
    editor.setSkills({"C++", "Python", "Java"});
    history.save(editor);

    editor.printResume();

    editor.setExperience("3 years at TechCorp");
    editor.setSkills({"C++", "Python", "Java", "Go"});
    history.save(editor);

    editor.printResume();

    cout << "Undoing last change..." << endl;
    history.undo(editor);
    editor.printResume();

    cout << "Undoing to original state..." << endl;
    history.undo(editor);
    editor.printResume();

    return 0;
}   
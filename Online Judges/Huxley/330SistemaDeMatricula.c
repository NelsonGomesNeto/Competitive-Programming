#include <stdio.h>
#include <string.h>
#define DEBUG if(0)

typedef struct student student_t;
typedef struct subject subject_t;
typedef struct studentSubject studentSubject_t;

struct student
{
  char code[31];
  char name[501];
  int year, sex;
  double enem;
};

struct subject
{
  char code[26];
  char name[101];
  int students;
};

struct studentSubject
{
  char studentCode[31], subjectCode[26];
};

void addToSubject(subject_t subjects[], int m, char subjectCode[])
{
  for (int i = 0; i < m; i ++)
    if (strcmp(subjects[i].code, subjectCode) == 0)
    {
      subjects[i].students ++;
      break;
    }
}

int getSubjectId(char code[], subject_t subjects[], int m)
{
  for (int i = 0; i < m; i ++)
    if (strcmp(code, subjects[i].code) == 0)
      return(i);
  return(-1);
}

int getStudentId(char code[], student_t students[], int n)
{
  for (int i = 0; i < n; i ++)
    if (strcmp(code, students[i].code) == 0)
  return(i);
  return(-1);
}

void swapSubjects(subject_t *a, subject_t *b)
{
  subject_t aux = *a;
  *a = *b;
  *b = aux;
}

void sortSubjects(subject_t subjects[], int m)
{
  for (int i = 0; i < m; i ++)
    for (int j = i + 1; j < m; j ++)
      if (strcmp(subjects[i].name, subjects[j].name) > 0)
        swapSubjects(&subjects[i], &subjects[j]);
}

void swapStudentSubjects(studentSubject_t *a, studentSubject_t *b)
{
  studentSubject_t aux = *a;
  *a = *b;
  *b = aux;
}

void sortStudentSubjects(studentSubject_t studentSubjects[], int p, student_t students[], int n, subject_t subjects[], int m)
{
  for (int i = 0; i < p; i ++)
    for (int j = i + 1; j < p; j ++)
    {
      int sui = getSubjectId(studentSubjects[i].subjectCode, subjects, m);
      int suj = getSubjectId(studentSubjects[j].subjectCode, subjects, m);
      int sti = getStudentId(studentSubjects[i].studentCode, students, n);
      int stj = getStudentId(studentSubjects[j].studentCode, students, n);
      if (strcmp(subjects[sui].name, subjects[suj].name) > 0
        || (strcmp(subjects[sui].name, subjects[suj].name) == 0 && strcmp(students[sti].name, students[stj].name) > 0))
        swapStudentSubjects(&studentSubjects[i], &studentSubjects[j]);
    }
}

int main()
{
  int h = 0, f = 0, upper = 0; double mean = 0, upperMean = 0;
  int n; scanf("%d", &n);
  student_t students[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("\n%s\n%[^\n]\n%d\n%d\n%lf", students[i].code, students[i].name, &students[i].year, &students[i].sex, &students[i].enem);
    h += students[i].sex == 1;
    f += students[i].sex == 0;
    mean += students[i].year;
    upperMean += students[i].enem > 7.5 ? students[i].year : 0;
    upper += students[i].enem > 7.5;
  }
  DEBUG for (int i = 0; i < n; i ++)
    printf("%s %s %d %d %lf\n", students[i].code, students[i].name, students[i].year, students[i].sex, students[i].enem);

  int m; scanf("%d", &m);
  subject_t subjects[m];
  for (int i = 0; i < m; i ++)
  {
    scanf("\n%s\n%[^\n]", subjects[i].code, subjects[i].name);
    subjects[i].students = 0;
  }
  DEBUG for (int i = 0; i < m; i ++)
    printf("%s %s\n", subjects[i].code, subjects[i].name);

  int p; scanf("%d", &p);
  studentSubject_t studentSubjects[p];
  for (int i = 0; i < p; i ++)
  {
    scanf("\n%s %s", studentSubjects[i].studentCode, studentSubjects[i].subjectCode);
    addToSubject(subjects, m, studentSubjects[i].subjectCode);
  }

  sortSubjects(subjects, m);
  sortStudentSubjects(studentSubjects, p, students, n, subjects, m);

  printf("%d\n%d\n%.2lf\n%.2lf\n", h, f, mean / n, upperMean / upper);
  for (int i = 0, mat = 0; i < m; i ++)
  {
    printf("%s\n%d\n", subjects[i].name, subjects[i].students);
    for (int j = 0; j < subjects[i].students; j ++)
    {
      int id = getStudentId(studentSubjects[mat ++].studentCode, students, n);
      printf("%s\n", students[id].name);
    }
  }
  return(0);
}

#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct lfloat
{
	float f;
	struct lfloat *px;
}lfloat;

typedef struct lint
{
	int i;
	struct lint *px;
}lint;


typedef struct OBJETO{
	lfloat *v;
	lfloat *vt;
	lfloat *vn;
	lint *f;
} OBJETO;

lint* insereli(lint *head, int x)
{
	lint* p = head;
	if (!p)
	{
		head = (lint*) calloc(1, sizeof(lint));
		head->i = x;
		head->px = NULL;
		return head;
	}
	while (p->px)p = p->px;

	p->px = (lint*) calloc(1, sizeof(lint));
	p->px->i = x;
	p->px->px = NULL;
}

lfloat* inserelf(lfloat *head, float x)
{
	lfloat* p = head;
	if (!p)
	{
		head = (lfloat*) calloc(1, sizeof(lfloat));
		head->f = x;
		head->px = NULL;
		return head;
	}
	while (p->px)p = p->px;

	p->px = (lfloat*) calloc(1, sizeof(lfloat));
	p->px->f = x;
	p->px->px = NULL;
}

void lerFace(char *linha, OBJETO *o)
{
	int x, y, z;
	char c;
	sscanf(linha,"%c %i %i %i", &c, &x, &y, &z);
	insereli(o->f, x);
	insereli(o->f, y);
	insereli(o->f, z);
}

void lerFloats(char *linha, OBJETO *o)
{
	float x, y, z;
	char str[3];
	sscanf(linha, "%s %f %f %f", str, &x, &y, &z);
	if (!str[1])
	{
		inserelf(o->v, x);
		inserelf(o->v, y);
		inserelf(o->v, z);
	}
	else if (str[1] == 't')
	{
		inserelf(o->vt, x);
		inserelf(o->vt, y);
		inserelf(o->vt, z);
	}
	else
	{
		inserelf(o->vn, x);
		inserelf(o->vn, y);
		inserelf(o->vn, z);
	}
}

OBJETO* loader(char* fname)
{
	FILE * file = fopen(fname, "rb");
	char linha[2048];
	char b;
	int i;

	OBJETO *obj;

	if (file == NULL){
		printf("arquivo invalido");
		exit(1);
	}
	i = 0;
	while (b != EOF)
	{
		obj = (OBJETO*) calloc(1,sizeof(OBJETO));
		obj->f = NULL;
		obj->v = obj->vt = obj->vn = NULL;

		while (b != 13 && b != EOF){
			fscanf(file, "%c", &b);
			linha[i] = b;
			i++;
		}

		linha[--i] = '\0';

		if (linha[0] == '#')/* ignore comentarios */;
		else if (linha[0] == 'f' && linha[1] == ' ') lerFace(linha,obj);
		else if (
			(linha[0] == 'v' && linha[1] == 'n' && linha[2] == ' ') ||
			(linha[0] == 'v' && linha[1] == 't' && linha[2] == ' ') ||
			(linha[0] == 'v' && linha[1] == ' ')
			) lerFloats(linha, obj);
	}

	return obj;
}
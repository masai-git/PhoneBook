#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//�\���̐錾
typedef struct _card
{
	char name[10];		//���O
	char num[10];		//�d�b�ԍ�
	struct _card* next;	//���ւ̃|�C���^
}CARD;

//�v���g�^�C�v�錾
void  add(char*, char*);
CARD* search(char*, int);

CARD* start = NULL;//�擪���o���Ă����|�C���^

int main(void)
{
	int i;
	char cmd[10], name[10], num[10];

	printf("*******    �d�b���A�v��    *******\n");
	printf("�ǁ@���@�� add    ���O �d�b�ԍ�\n");
	printf("���@���@�� search ���O\n");
	printf("�S���\���� list\n");
	printf("\n");

	while (1)	//�����ƌJ��Ԃ�(exit�R�}���h��break)
	{
		//�R�}���h�̓���
		scanf_s("%s", cmd, 10);
		//�啶���œ��͂����ꍇ�ł��������ɕϊ�����
		for (i = 0; i < strlen(cmd); i++)
			cmd[i] 
			= 
			tolower(cmd[i]);

		if (strcmp(cmd, "exit") == 0)
		{
			//exit�R�}���h�̏ꍇ
			break;
		}
		else if (strcmp(cmd, "add") == 0)
		{
			//add�R�}���h�̏ꍇ
			//���O�A�d�b�ԍ������
			scanf_s("%s", name, 10);
			scanf_s("%s", num, 10);
			//�ǉ�����
			add(name, num);
		}
		else if (strcmp(cmd, "list") == 0)
		{
			//list�R�}���h�̏ꍇ
			//�S����ʕ\��
			CARD* card = start;
			while (card != NULL)
			{
				printf("%s %s\n", card->name, card->num);
				card = card->next;
			}
		}
		else if (strcmp(cmd, "search") == 0)
		{
			//search�R�}���h�̏ꍇ
			//���O�����
			scanf_s("%s", name, 10);
			//�������ʂ���ʕ\��
			CARD* card = search(name,0);
			if (card != NULL)
			{
				printf("%s %s\n", card->name, card->num);
			}
			else
			{
				printf("%s �̓o�^������܂���B\n",name);
			}
		}
	}
}

void add(char* name, char* num)
{
	//�V�����̈���m��
	CARD* newCard = (CARD*)malloc(sizeof(CARD)),*beforeCard;
	//���O�Ɠd�b�ԍ���V�����̈�ɐݒ�
	strcpy(newCard->name, name);
	strcpy(newCard->num, num);

	//�}���ʒu���������A�O�̃J�[�h��next�Ǝ������g��next��ݒ�
	beforeCard = search(name, 1);
	if (beforeCard == NULL)
	{
		if (start == NULL)
		{
			//�P���o�^���Ȃ��ꍇ
			newCard->next = NULL;
		}
		else
		{
			//�ǉ������J�[�h���擪�̏ꍇ
			newCard->next = start;
		}
		start = newCard;
	}
	else
	{
		newCard->next = beforeCard->next;
		beforeCard->next = newCard;
	}
}

CARD* search(char* name,int flg) //flg:0=���O����v�����A�h���X��Ԃ� 1:�ЂƂO�̃A�h���X��Ԃ�
{
	CARD* p = start,*bf=NULL;
	if (start == NULL)
	{
		//�P���o�^���Ȃ��ꍇNULL��Ԃ�
		return NULL;
	}
	else
	{
		if (flg == 0)
		{
			//���O����v������̂�T��
			while (p != NULL && strcmp(name,p->name) != 0)
			{
				p = p->next;
			}
			return p;
		}
		else
		{
			//a-z���Œǉ�����ʒu��T��
			while (p != NULL && strcmp(name, p->name) >= 0)
			{
				bf = p;
				p = p->next;
			}
			return bf;
		}
	}

}

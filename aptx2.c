#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int cnt,c,i,j,*x_position,*y_position,*time,*apple_step;
	int my_step,my_position;
	int x_position_tmp,flg,apple_tmp;
	FILE *input_f,*move;
		if((input_f=fopen("apple.txt","r"))==NULL){
				fprintf(stderr,"�t�@�C���̓ǂݍ��ݎ��s");
				exit(EXIT_FAILURE);
				}
				
		if((move=fopen("movetest.txt","a"))==NULL){
				fprintf(stderr,"�t�@�C���̓ǂݍ��ݎ��s");
				exit(EXIT_FAILURE);
				}
				
				while((c=fgetc(input_f))!=EOF){		//�ꕶ�����ǂݍ���
				  if(c=='\n')				//���s�Ńv���X 
 				cnt++;
				  }
		     	printf("%d\n",cnt);					//�s���m�F
		     	
		     	
		     	//�z��̓��I�m��
		    	 	x_position=(int *)malloc(sizeof(int)*cnt);
				y_position=(int *)malloc(sizeof(int)*cnt);
				time=(int *)malloc(sizeof(int)*cnt);
				apple_step=(int *)malloc(sizeof(int)*cnt);
				if(x_position==NULL&&y_position==NULL&&time==NULL&&apple_step==NULL){
				fprintf(stderr,"malloc error\n");
				return 1;
		}
		rewind(input_f);								//�ǂݍ��݈ʒu���Z�b�g
		for(i=0;i<cnt;i++){
		fscanf(input_f,"%d,%d,%d\n",&x_position[i],&y_position[i],&time[i]);
		printf("%d,%d,%d\n",x_position[i],y_position[i],time[i]);	//�i�[�m�F
     	}
		
		for(i=0;i<cnt;i++){          //��񂲂̗�������
			apple_step[i]=y_position[i]*5+time[i];
		printf("%d\n",apple_step[i]);  //�e�������Ԃ̊m�F
		}
		
	
		//apple_time���v�Z�A���������Ƀ\�[�g�Ax_position�Ɗ֘A�Â��Ĉ�ԏ������Ƃ��납�瓞�B�\�ł���Έړ��A�s�\�ł���Ύ��Ɉړ��B
		for(i=0;i<cnt;i++){						//�����Ƀ\�[�g
		for(j=i+1;j<cnt+1;j++){
			if(apple_step[i]>apple_step[j]){
				
				apple_tmp=apple_step[i];		//apple_step�������Ƀ\�[�g
				apple_step[i]=apple_step[j];
				apple_step[j]=apple_tmp;
				
				x_position_tmp=x_position[i];	//x_position��apple_step�Ɗ֘A�t���ď����\�[�g
				x_position[i]=x_position[j];
				x_position[j]=x_position_tmp;
				}
			}
		}
		i=0;
		fprintf(move,"%d",x_position[0]);
		while(my_step<=apple_step[cnt-1]){ 		//��������my_step��apple_step���z����܂�
			if(abs(x_position[i]-my_position)<(apple_step[i]-my_step)){
				while(flg=0){
				if(my_position==x_position[i]){
					for(j=my_step;j<apple_step[i];j++){
									fprintf(move,"s,");
					}
					my_step=apple_step[i];		 //������Ƃ��̂݃X�e�b�v���v���X�B
					flg=1;
				}
				else if(my_position<x_position[i]){
						for(j=0;j<apple_step[my_step];j++){
						fprintf(move,"r,");
						my_step++;
					}
				}
				else if(my_position>x_position[i]){
						for(j=0;j<apple_step[my_step];j++){
							fprintf(move,"l,");
							my_step++;
					}
				}
			}
			}
			else{}
			my_position=x_position[i];
			i++;
			flg=0;
	}
	
fclose(input_f);
fclose(move);
}

//yp*5+tm�Ŏ擾

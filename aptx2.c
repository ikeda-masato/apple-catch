#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int cnt,c,i,j,*x_position,*y_position,*time,*apple_step;
	int my_step,my_position;
	int x_position_tmp,flg,apple_tmp;
	FILE *input_f,*move;
		if((input_f=fopen("apple.txt","r"))==NULL){
				fprintf(stderr,"ファイルの読み込み失敗");
				exit(EXIT_FAILURE);
				}
				
		if((move=fopen("movetest.txt","a"))==NULL){
				fprintf(stderr,"ファイルの読み込み失敗");
				exit(EXIT_FAILURE);
				}
				
				while((c=fgetc(input_f))!=EOF){		//一文字ずつ読み込み
				  if(c=='\n')				//改行でプラス 
 				cnt++;
				  }
		     	printf("%d\n",cnt);					//行数確認
		     	
		     	
		     	//配列の動的確保
		    	 	x_position=(int *)malloc(sizeof(int)*cnt);
				y_position=(int *)malloc(sizeof(int)*cnt);
				time=(int *)malloc(sizeof(int)*cnt);
				apple_step=(int *)malloc(sizeof(int)*cnt);
				if(x_position==NULL&&y_position==NULL&&time==NULL&&apple_step==NULL){
				fprintf(stderr,"malloc error\n");
				return 1;
		}
		rewind(input_f);								//読み込み位置リセット
		for(i=0;i<cnt;i++){
		fscanf(input_f,"%d,%d,%d\n",&x_position[i],&y_position[i],&time[i]);
		printf("%d,%d,%d\n",x_position[i],y_position[i],time[i]);	//格納確認
     	}
		
		for(i=0;i<cnt;i++){          //りんごの落下時間
			apple_step[i]=y_position[i]*5+time[i];
		printf("%d\n",apple_step[i]);  //各落下時間の確認
		}
		
	
		//apple_timeを計算、小さい順にソート、x_positionと関連づけて一番小さいところから到達可能であれば移動、不可能であれば次に移動。
		for(i=0;i<cnt;i++){						//昇順にソート
		for(j=i+1;j<cnt+1;j++){
			if(apple_step[i]>apple_step[j]){
				
				apple_tmp=apple_step[i];		//apple_stepを昇順にソート
				apple_step[i]=apple_step[j];
				apple_step[j]=apple_tmp;
				
				x_position_tmp=x_position[i];	//x_positionをapple_stepと関連付けて昇順ソート
				x_position[i]=x_position[j];
				x_position[j]=x_position_tmp;
				}
			}
		}
		i=0;
		fprintf(move,"%d",x_position[0]);
		while(my_step<=apple_step[cnt-1]){ 		//もしくはmy_stepがapple_stepを越えるまで
			if(abs(x_position[i]-my_position)<(apple_step[i]-my_step)){
				while(flg=0){
				if(my_position==x_position[i]){
					for(j=my_step;j<apple_step[i];j++){
									fprintf(move,"s,");
					}
					my_step=apple_step[i];		 //消費したときのみステップをプラス。
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

//yp*5+tmで取得

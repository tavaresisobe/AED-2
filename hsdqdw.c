/* Programa: AP8 - Arvore AVL x Arvore RN

   Autor: Gustavo Henrique Tavares Isobe

   Versao: 3.0 - 29/05/2023 - 02:00h

*/
//teste 10
//input
//934 635 860 1065 737 859 1044 618 708 992 636 1114 866 779 753 784 683 806 1131 997 704 1006 1141 876 761 1011 959 1169 746 781 721 831 1167 733 1047 1055 743 891 825 851 1034 612 1116 700 790 669 624 626 1165 1021 1081 722 961 757 634 771 867 603 668 799 1075 651 1117 607 1097 724 1102 1139 948 752 973 667 824 900 1087 610 923 865 1175 1095 745 1048 855 653 1082 778 672 1084 1197 870 710 647 1069 1144 662 970 1121 606 1119 939 1181 1170 1178 1191 644 1194 738 1012 1145 1143 645 614 1128 719 883 990 1173 858 1060 627 694 794 1147 699 1064 637 680 785 966 1022 829 986 767 1149 711 1039 1185 804 873 838 971 811 671 1183 1196 697 676 995 1126 1005 1032 957 1190 797 908 915 1088 1156 616 950 609 949 633 1140 1186 911 796 893 792 720 1008 889 754 630 931 1199 847 646 1086 802 661 836 947 921 695 805 861 1171 980 920 615 933 734 1092 835 773 774 1014 1123 772 1009 623 996 1071 795 716 917 999 976 748 698 1127 712 849 605 845 1096 775 730 857 1122 655 826 632 604 654 751 820 1200 888 994 788 714 872 955 715 918 1134 1059 956 787 685 987 1142 786 793 1045 942 856 693 747 1098 964 639 853 932 914 1130 1002 718 815 744 1176 682 709 1198 755 844 938 937 631 1030 1089 1184 741 974 897 742 958 1153 1066 902 1118 1056 1113 827 807 850 1164 1189 868 625 687 910 608 1179 657 1070 963 896 1110 969 1007 1177 943 1135 1192 1023 899 1099 1067 1111 732 756 764 665 946 1010 688 944 1031 854 1159 1052 1057 906 656 1168 673 981 984 611 1027 1083 749 919 962 1077 770 1151 686 828 998 1040 1105 1058 809 988 706 877 1180 768 702 979 701 1076 1109 913 1085 880 925 907 782 808 800 1166 953 1120 643 650 1090 726 818 703 666 814 617 652 1054 763 1041 1024 1172 927 1015 739 791 1132 928 912 783 848 1155 1125 890 717 1049 1018 1138 881 967 684 1046 613 1062 812 940 819 801 846 658 728 664 649 601 952 929 909 810 930 834 659 1157 1042 750 843 1137 821 936 1150 1043 960 875 898 977 1026 689 1188 789 660 989 776 725 803 837 620 852 904 736 619 841 965 690 629 832 735 884 1129 1148 1035 1187 642 991 1053 1036 968 830 670 823 1112 1104 892 842 1136 677 1101 1016 924 1093 1013 1003 675 916 903 1025 1193 740 985 1115 935 1103 705 885 692 691 1017 678 869 975 1108 1161 839 864 723 640 638 1174 648 762 905 713 901 622 1037 760 817 941 978 1020 1074 982 759 1063 894 1073 766 1061 1158 707 1091 983 1107 641 1182 1029 863 813 1051 681 882 1000 871 1146 602 1028 993 729 798 862 674 1160 886 874 1004 731 769 628 945 1152 926 758 1001 822 878 1038 1019 1050 840 895 1162 833 1079 1163 1080 887 765 1133 954 816 663 727 1195 951 1106 777 621 972 679 1033 879 1078 696 1068 1094 922 1100 1124 1154 1072 780 -1
//output
//10, 10, 10
//10, 10, 10
//6
//1378, 346, 291

// ##################### Bibliotecas Externas ##############################

	

#include <stdio.h>

#include <stdlib.h>



// ########################## TAD X.h ######################################



struct tipoABB_RN{ //Arvore Rubro Negra

    int chave ;

	struct tipoABB_RN* pai ; // noh pai

	struct tipoABB_RN* esq ;

	struct tipoABB_RN* dir ;

	int cor ; // 0 - Negra, 1 - Rubro

};



//ponteiro para a raiz

struct tipoABB_RN* root = NULL;



struct ABB_AVL{ //Arvore AVL

    int chave ;

    struct ABB_AVL *esq ;

    struct ABB_AVL *dir ;

    int h ;

};

typedef struct ABB_AVL TipoArvore ;

typedef TipoArvore* TipoABB_AVL ;



// ###################### Funcoes e Procedimentos do programa - ABB RUBRO NEGRA ##############



//Obs.: Removi todas funcoes que nao serao utilizadas



//retorna maior valor entre de 2 elementos

int max(int a, int b)

{

  if(a > b)

    return a;

  else

    return b;

}



//rotacao para a esquerda:

void rotacionaDir(struct tipoABB_RN* aux)

{

	struct tipoABB_RN* esquerda = aux->esq ;

	aux->esq = esquerda->dir ;

	if (aux->esq)

		aux->esq->pai = aux ;

	esquerda->pai = aux->pai ;

	if (!aux->pai)

	{

		root = esquerda ;

	}else if (aux == aux->pai->esq)

	{

		aux->pai->esq = esquerda ;

	}else

		aux->pai->dir = esquerda ;

	esquerda->dir = aux ;

	aux->pai = esquerda ;

}



//rotacao para a direita

void rotacionaEsq(struct tipoABB_RN* aux)

{

	struct tipoABB_RN* direita = aux->dir ;

	aux->dir = direita->esq ;

	if (aux->dir)

		aux->dir->pai = aux ;

	direita->pai = aux->pai ;

	if (!aux->pai)

	{

		root = direita ;

	}else if (aux == aux->pai->esq){

		aux->pai->esq = direita ;

	}else

		aux->pai->dir = direita ;

	direita->esq = aux ;

	aux->pai = direita ;

}



//busca o No, onde sera inserido o no folha

struct tipoABB_RN* buscaPai(struct tipoABB_RN* raiz, 

                                struct tipoABB_RN* aux)

{

	//caso AbbRN estiver vazia

	if (raiz == NULL)

		return aux ;



	if (aux->chave < raiz->chave)

	{

		raiz->esq = buscaPai(raiz->esq, aux) ;

		raiz->esq->pai = raiz ;

	}

	else if (aux->chave > raiz->chave)

	{

		raiz->dir = buscaPai(raiz->dir, aux) ;

		raiz->dir->pai = raiz ;

	}

	return raiz ;

}



struct tipoABB_RN* criaNo(int chave)

{

    struct tipoABB_RN* aux

			= (struct tipoABB_RN*)malloc(sizeof(struct tipoABB_RN)) ;

	if (aux)

	{

		aux->esq = NULL ;

		aux->dir = NULL ;

		aux->pai = NULL ;

		aux->chave = chave ;

		aux->cor = 1 ;

	}else

	    printf ("Erro ao alocar memoria\n") ;

	return aux ;

}



void insereABBRubroNegra(int chave, int *mudacor, int *rotate)

{

    struct tipoABB_RN* temp = criaNo(chave) ;

    if (temp)

    {

        //insere o novo noh, e retorna seu rrespectivo no pai

		root = buscaPai(root, temp) ;

		fixup(root, temp, mudacor, rotate) ;

		root->cor = 0 ;

    }

}



//funcao para concertar desbalanceamento causado pela insercao

void fixup(struct tipoABB_RN* raiz, struct tipoABB_RN* aux, 

            int *mudacor, int *rotate)

{

	struct tipoABB_RN* pai = NULL ;

	struct tipoABB_RN* avo = NULL ;



	while ((aux != raiz) && (aux->cor != 0)

		&& (aux->pai->cor == 1))

	{

		pai = aux->pai ;

		avo = aux->pai->pai ;

		

		//rotacoes para esquerda:

		if (pai == avo->esq)

		{

			struct tipoABB_RN* tio_esq_aux = avo->dir ;

			if (tio_esq_aux != NULL && tio_esq_aux->cor == 1)

			{

			    if (avo->cor != 1)

			    {

			        avo->cor = 1 ;

			        *mudacor += 1 ;

			    }

			    if (pai->cor != 0)

			    {

				    pai->cor = 0 ;

				    *mudacor += 1 ;

				}

				if (tio_esq_aux->cor != 0)

				{

				    tio_esq_aux->cor = 0 ;

				    *mudacor += 1 ;

				}

				aux = avo ;

			}else{

				if (aux == pai->dir)

				{

					rotacionaEsq(pai) ;

					*rotate += 1 ;

					aux = pai ;

					pai = aux->pai ;

				}

			    rotacionaDir(avo) ;

			    *rotate += 1 ;

				int t = pai->cor ;

				if (pai->cor != avo->cor)

				{

				    pai->cor = avo->cor ;

				    *mudacor += 1 ;

				}

				if (avo->cor != t)

				{

				    avo->cor = t ;

				    *mudacor += 1 ;

				}

				aux = pai ;

			}

		}



		//rotacoes para direita:

		else {

			struct tipoABB_RN* tio_dir_aux = avo->esq ;

			if ((tio_dir_aux != NULL) && (tio_dir_aux->cor == 1))

			{

			    if (avo->cor != 1)

			    {

			        avo->cor =  1 ;

			        *mudacor += 1 ;

				}

				if (pai->cor != 0)

				{

				    pai->cor = 0 ;

				    *mudacor += 1 ;

				}

				if(tio_dir_aux->cor != 0)

				{

				    tio_dir_aux->cor = 0 ;

				    *mudacor += 1 ;

				}

				aux = avo ;

			}else{

				if (aux == pai->esq)

				{

					rotacionaDir(pai) ;

					*rotate += 1 ;

					aux = pai ;

					pai = aux->pai ;

				}



				rotacionaEsq(avo) ;

				*rotate += 1 ;

				int t = pai->cor ;

				if (pai->cor != avo->cor)

				{

				    pai->cor = avo->cor ;

				    *mudacor += 1 ;

				}

				if (avo->cor != t)

				{

				    avo->cor = t ;

				    *mudacor += 1 ;

				}

				aux = pai ;

			}

		}

	}

}



int alturaNoPreto(struct tipoABB_RN* aux, int *count)

{

    if (aux != NULL && aux->cor == 0)

        *count += 1 ;

    if (aux->dir != NULL && aux->dir->cor == 0)

        alturaNoPreto(aux->dir, count) ;

    if (aux->esq != NULL && aux->esq->cor == 0)

        alturaNoPreto(aux->esq, count) ;

    return *count ;

}



//funcao para calcular altura da AbbRN

int alturaRN(struct tipoABB_RN* aux)

{

        if(aux == NULL)

            return 0 ;

        else

            return 1 + max(alturaRN(aux->esq), alturaRN(aux->dir)) ;

}



void preordem(struct tipoABB_RN* aux)

{

    if (aux!= NULL)

        printf("%d-%d  ", aux->chave, aux->cor) ;

    if (aux->dir != NULL)

        preordem(aux->dir) ;

    if (aux->esq != NULL)

        preordem(aux->esq) ;

}



// ###################### Funcoes e Procedimentos do programa - ABB AVL ##############



int arvoreVazia(TipoABB_AVL aux)

{

    return aux == NULL ;

}



TipoABB_AVL inicializaArvore()

{

    return NULL ;

}



TipoABB_AVL insereNo(int num)

{

    TipoABB_AVL novo = (TipoABB_AVL)malloc(sizeof(TipoArvore)) ;

    if (novo)

    {

        novo->chave = num ;

        novo->esq = NULL ;

        novo->dir = NULL ;

        novo->h = 1 ;

    }else

        printf ("Erro ao alocar memoria\n") ;

    return novo ;

}



int altura(TipoABB_AVL aux)

{

    if(aux == NULL) return 0 ;

    return aux->h ;

}



TipoABB_AVL rotaciona_dir_avl(TipoABB_AVL aux)

{

    TipoABB_AVL x = aux->esq ; 

    aux->esq = x->dir ;

    x->dir = aux ;

    

    aux->h = max(altura(aux->esq),altura(aux->dir)) + 1 ;

    x->h = max(altura(x->esq),altura(x->dir)) + 1 ;

 

    return x ;

  

}



TipoABB_AVL rotaciona_esq_avl(TipoABB_AVL aux)

{

    TipoABB_AVL x = aux->dir ; 

    aux ->dir = x->esq ;

    x->esq = aux ;

    

    aux->h = max(altura(aux->esq),altura(aux->dir)) + 1 ;

    x->h = max(altura(x->esq),altura(x->dir)) + 1 ;



    return x ;

  

}



TipoABB_AVL rotaciona_esq_dir(TipoABB_AVL aux)

{

    aux->esq = rotaciona_esq_avl(aux->esq) ;

    return rotaciona_dir_avl(aux) ;

}



TipoABB_AVL rotaciona_dir_esq(TipoABB_AVL aux)

{

    aux->dir = rotaciona_dir_avl(aux->dir) ;

    return rotaciona_esq_avl(aux) ;

}



int fb(TipoABB_AVL aux)

{

    if (aux == NULL)

        return 0 ;

    return altura(aux->esq) - altura(aux->dir) ;

}





TipoABB_AVL insereAVL(TipoABB_AVL aux, int info, int* rotate_avl)

{

    if (aux == NULL)

        return insereNo(info) ;

    if (info < aux->chave)

        aux->esq = insereAVL(aux->esq, info, rotate_avl) ;

    else if (info > aux->chave)

        aux->dir = insereAVL(aux->dir, info, rotate_avl) ;

    else

        return aux ; 



    aux->h = max(altura(aux->esq), altura(aux->dir))+1 ;



    // verifica o fator de balanceamento da arvore avl

    int x = fb(aux) ;



    if (x > 1 && fb(aux->esq) >= 0)

    {

        *rotate_avl += 1 ;

        return rotaciona_dir_avl(aux) ;

    }

    if (x < -1 && fb(aux->dir) <= 0)

    {

        *rotate_avl += 1 ;

        return rotaciona_esq_avl(aux) ;

    }

    if (x > 1 && fb(aux->esq) < 0)

    {

        *rotate_avl += 1 ;

        return rotaciona_esq_dir(aux) ;

    }

    if (x < -1 && fb(aux->dir) > 0) 

    {

        *rotate_avl += 1 ;

        return rotaciona_dir_esq(aux) ;

    }

    return aux ;

}



int alturaAVL(TipoABB_AVL aux)

{

    if(aux == NULL)

            return 0 ;

        else

            return 1 + max(alturaAVL(aux->esq), alturaAVL(aux->dir)) ;

}



// ############################ Principal ###################################



int main()

{

    TipoABB_AVL raiz = inicializaArvore(),aux ;

	int i = 0, j, n ;

    int vet[100] ;

	scanf ("%d", &n) ;

    while (n != -1)

    {

        vet[i] = n ;

        scanf ("%d", &n) ;

        i++ ;

    }

    if (i > 0)

    {

        int rotate_avl = 0 ;

	    for (j = 0 ; j < i ; j++)

	    {

	        raiz = insereAVL(raiz, vet[j], &rotate_avl) ;

	    }

        printf("%d,%d,%d\n",alturaAVL(raiz)-1, 

            alturaAVL(raiz->esq),alturaAVL(raiz->dir)) ;

    

        int mudacor = 0, rotate = 0, c_esq = 0, c_dir = 0 ;

	    for (j = 0 ; j < i ; j++)

	    {

	        insereABBRubroNegra(vet[j], &mudacor, &rotate) ;

	    }

	    //preordem(root) ;

	    //preordem(raiz) ;

	    printf ("%d,%d,%d\n", alturaRN(root)-1, alturaRN(root->esq),

	                alturaRN(root->dir)) ;

        printf ("%d\n", max(alturaNoPreto(root->dir, &c_dir), alturaNoPreto(root->esq, &c_esq))) ;

	    printf ("%d,%d,%d\n", mudacor, rotate, rotate_avl) ;

	}

	return 0 ;

}


/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/* 
 * Please fill in the following student struct 
 */
team_t team = {
    "2171155",              /* Student ID */

    "Adil Kaan Akan",     /* full name */
    "kaan.akan@metu.edu.tr",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};


/***************
 * CONVOLUTION KERNEL
 ***************/

/******************************************************
 * Your different versions of the convolution functions  go here
 ******************************************************/

/* 
 * naive_conv - The naive baseline version of convolution 
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim,int *src, int *ker,int *dst) {
    int i,j,k,l;

    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            dst[j*dim+i] = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    dst[j*dim+i] = dst[j*dim+i] +src[(j+l)*dim+(i+k)]*ker[l*dim+k];
                }
        }
            
        
}

void convo(int dim, int *src, int *ker,int *dst){
    int * temp_ker = ker;
    int ker_0  = temp_ker[0];
    int ker_1  = temp_ker[1];
    int ker_2  = temp_ker[2];
    int ker_3  = temp_ker[3];
    int ker_4  = temp_ker[4];
    int ker_5  = temp_ker[5];
    int ker_6  = temp_ker[6];
    int ker_7  = temp_ker[7];
    temp_ker += dim;
    int ker_8  = temp_ker[0];
    int ker_9  = temp_ker[1];
    int ker_10 = temp_ker[2];
    int ker_11 = temp_ker[3];
    int ker_12 = temp_ker[4];
    int ker_13 = temp_ker[5];
    int ker_14 = temp_ker[6];
    int ker_15 = temp_ker[7];
    temp_ker += dim;
    int ker_16 = temp_ker[0];
    int ker_17 = temp_ker[1];
    int ker_18 = temp_ker[2];
    int ker_19 = temp_ker[3];
    int ker_20 = temp_ker[4];
    int ker_21 = temp_ker[5];
    int ker_22 = temp_ker[6];
    int ker_23 = temp_ker[7];
    temp_ker += dim;
    int ker_24 = temp_ker[0];
    int ker_25 = temp_ker[1];
    int ker_26 = temp_ker[2];
    int ker_27 = temp_ker[3];
    int ker_28 = temp_ker[4];
    int ker_29 = temp_ker[5];
    int ker_30 = temp_ker[6];
    int ker_31 = temp_ker[7];
    temp_ker += dim;
    int ker_32 = temp_ker[0];
    int ker_33 = temp_ker[1];
    int ker_34 = temp_ker[2];
    int ker_35 = temp_ker[3];
    int ker_36 = temp_ker[4];
    int ker_37 = temp_ker[5];
    int ker_38 = temp_ker[6];
    int ker_39 = temp_ker[7];
    temp_ker += dim;
    int ker_40 = temp_ker[0];
    int ker_41 = temp_ker[1];
    int ker_42 = temp_ker[2];
    int ker_43 = temp_ker[3];
    int ker_44 = temp_ker[4];
    int ker_45 = temp_ker[5];
    int ker_46 = temp_ker[6];
    int ker_47 = temp_ker[7];
    temp_ker += dim;
    int ker_48 = temp_ker[0];
    int ker_49 = temp_ker[1];
    int ker_50 = temp_ker[2];
    int ker_51 = temp_ker[3];
    int ker_52 = temp_ker[4];
    int ker_53 = temp_ker[5];
    int ker_54 = temp_ker[6];
    int ker_55 = temp_ker[7];
    temp_ker += dim;
    int ker_56 = temp_ker[0];
    int ker_57 = temp_ker[1];
    int ker_58 = temp_ker[2];
    int ker_59 = temp_ker[3];
    int ker_60 = temp_ker[4];
    int ker_61 = temp_ker[5];
    int ker_62 = temp_ker[6];
    int ker_63 = temp_ker[7];
    int i, j;
    int val4, val1, val2, val3;
    int *src_element_pointer, *dst_element_pointer, *src_8_row_pointer, *src_8_row_pointer2, *src_8_row_pointer3, *src_8_row_pointer4;
    int dim_7 = dim - 7;
    for(i = 0; i < dim_7; i++, dst += dim, src += dim){
        for(j = 0, dst_element_pointer = dst, src_element_pointer = src; j < dim_7; j += 4, src_element_pointer += 4, dst_element_pointer += 4) {
            /*
            val = val1 = val2 = val3 = 0;
            src_8_row_pointer = src_element_pointer;
            src_8_row_pointer2 = src_element_pointer + 1;
            src_8_row_pointer3 = src_element_pointer + 2;
            src_8_row_pointer4 = src_element_pointer + 3;

            val  += src_8_row_pointer[0]*ker_0;
            val  += src_8_row_pointer[1]*ker_1;
            val  += src_8_row_pointer[2]*ker_2;
            val  += src_8_row_pointer[3]*ker_3;
            val  += src_8_row_pointer[4]*ker_4;
            val  += src_8_row_pointer[5]*ker_5;
            val  += src_8_row_pointer[6]*ker_6;
            val  += src_8_row_pointer[7]*ker_7;
            
            val1  += src_8_row_pointer2[0]*ker_0;
            val1  += src_8_row_pointer2[1]*ker_1;
            val1  += src_8_row_pointer2[2]*ker_2;
            val1  += src_8_row_pointer2[3]*ker_3;
            val1  += src_8_row_pointer2[4]*ker_4;
            val1  += src_8_row_pointer2[5]*ker_5;
            val1  += src_8_row_pointer2[6]*ker_6;
            val1  += src_8_row_pointer2[7]*ker_7;

            val2  += src_8_row_pointer3[0]*ker_0;
            val2  += src_8_row_pointer3[1]*ker_1;
            val2  += src_8_row_pointer3[2]*ker_2;
            val2  += src_8_row_pointer3[3]*ker_3;
            val2  += src_8_row_pointer3[4]*ker_4;
            val2  += src_8_row_pointer3[5]*ker_5;
            val2  += src_8_row_pointer3[6]*ker_6;
            val2  += src_8_row_pointer3[7]*ker_7;

            val3  += src_8_row_pointer4[0]*ker_0;
            val3  += src_8_row_pointer4[1]*ker_1;
            val3  += src_8_row_pointer4[2]*ker_2;
            val3  += src_8_row_pointer4[3]*ker_3;
            val3  += src_8_row_pointer4[4]*ker_4;
            val3  += src_8_row_pointer4[5]*ker_5;
            val3  += src_8_row_pointer4[6]*ker_6;
            val3  += src_8_row_pointer4[7]*ker_7;

			
            src_8_row_pointer += dim;
            src_8_row_pointer2 +=dim;
            src_8_row_pointer3 +=dim;
            src_8_row_pointer4 +=dim;


            val  += src_8_row_pointer[0]*ker_8;
            val  += src_8_row_pointer[1]*ker_9;
            val  += src_8_row_pointer[2]*ker_10;
            val  += src_8_row_pointer[3]*ker_11;
            val  += src_8_row_pointer[4]*ker_12;
            val  += src_8_row_pointer[5]*ker_13;
            val  += src_8_row_pointer[6]*ker_14;
            val  += src_8_row_pointer[7]*ker_15;
            
            val1  += src_8_row_pointer2[0]*ker_8;
            val1  += src_8_row_pointer2[1]*ker_9;
            val1  += src_8_row_pointer2[2]*ker_10;
            val1  += src_8_row_pointer2[3]*ker_11;
            val1  += src_8_row_pointer2[4]*ker_12;
            val1  += src_8_row_pointer2[5]*ker_13;
            val1  += src_8_row_pointer2[6]*ker_14;
            val1  += src_8_row_pointer2[7]*ker_15;

            val2  += src_8_row_pointer3[0]*ker_8;
            val2  += src_8_row_pointer3[1]*ker_9;
            val2  += src_8_row_pointer3[2]*ker_10;
            val2  += src_8_row_pointer3[3]*ker_11;
            val2  += src_8_row_pointer3[4]*ker_12;
            val2  += src_8_row_pointer3[5]*ker_13;
            val2  += src_8_row_pointer3[6]*ker_14;
            val2  += src_8_row_pointer3[7]*ker_15;

            val3  += src_8_row_pointer4[0]*ker_8;
            val3  += src_8_row_pointer4[1]*ker_9;
            val3  += src_8_row_pointer4[2]*ker_10;
            val3  += src_8_row_pointer4[3]*ker_11;
            val3  += src_8_row_pointer4[4]*ker_12;
            val3  += src_8_row_pointer4[5]*ker_13;
            val3  += src_8_row_pointer4[6]*ker_14;
            val3  += src_8_row_pointer4[7]*ker_15;
			
            src_8_row_pointer += dim;
            src_8_row_pointer2 +=dim;
            src_8_row_pointer3 +=dim;
            src_8_row_pointer4 +=dim;

            val  += src_8_row_pointer[0]*ker_16;
            val  += src_8_row_pointer[1]*ker_17;
            val  += src_8_row_pointer[2]*ker_18;
            val  += src_8_row_pointer[3]*ker_19;
            val  += src_8_row_pointer[4]*ker_20;
            val  += src_8_row_pointer[5]*ker_21;
            val  += src_8_row_pointer[6]*ker_22;
            val  += src_8_row_pointer[7]*ker_23;
            
            val1  += src_8_row_pointer2[0]*ker_16;
            val1  += src_8_row_pointer2[1]*ker_17;
            val1  += src_8_row_pointer2[2]*ker_18;
            val1  += src_8_row_pointer2[3]*ker_19;
            val1  += src_8_row_pointer2[4]*ker_20;
            val1  += src_8_row_pointer2[5]*ker_21;
            val1  += src_8_row_pointer2[6]*ker_22;
            val1  += src_8_row_pointer2[7]*ker_23;

            val2  += src_8_row_pointer3[0]*ker_16;
            val2  += src_8_row_pointer3[1]*ker_17;
            val2  += src_8_row_pointer3[2]*ker_18;
            val2  += src_8_row_pointer3[3]*ker_19;
            val2  += src_8_row_pointer3[4]*ker_20;
            val2  += src_8_row_pointer3[5]*ker_21;
            val2  += src_8_row_pointer3[6]*ker_22;
            val2  += src_8_row_pointer3[7]*ker_23;

            val3  += src_8_row_pointer4[0]*ker_16;
            val3  += src_8_row_pointer4[1]*ker_17;
            val3  += src_8_row_pointer4[2]*ker_18;
            val3  += src_8_row_pointer4[3]*ker_19;
            val3  += src_8_row_pointer4[4]*ker_20;
            val3  += src_8_row_pointer4[5]*ker_21;
            val3  += src_8_row_pointer4[6]*ker_22;
            val3  += src_8_row_pointer4[7]*ker_23;
			
            src_8_row_pointer += dim;
            src_8_row_pointer2 +=dim;
            src_8_row_pointer3 +=dim;
            src_8_row_pointer4 +=dim;

            val  += src_8_row_pointer[0]*ker_24;
            val  += src_8_row_pointer[1]*ker_25;
            val  += src_8_row_pointer[2]*ker_26;
            val  += src_8_row_pointer[3]*ker_27;
            val  += src_8_row_pointer[4]*ker_28;
            val  += src_8_row_pointer[5]*ker_29;
            val  += src_8_row_pointer[6]*ker_30;
            val  += src_8_row_pointer[7]*ker_31;
            
            val1  += src_8_row_pointer2[0]*ker_24;
            val1  += src_8_row_pointer2[1]*ker_25;
            val1  += src_8_row_pointer2[2]*ker_26;
            val1  += src_8_row_pointer2[3]*ker_27;
            val1  += src_8_row_pointer2[4]*ker_28;
            val1  += src_8_row_pointer2[5]*ker_29;
            val1  += src_8_row_pointer2[6]*ker_30;
            val1  += src_8_row_pointer2[7]*ker_31;

            val2  += src_8_row_pointer3[0]*ker_24;
            val2  += src_8_row_pointer3[1]*ker_25;
            val2  += src_8_row_pointer3[2]*ker_26;
            val2  += src_8_row_pointer3[3]*ker_27;
            val2  += src_8_row_pointer3[4]*ker_28;
            val2  += src_8_row_pointer3[5]*ker_29;
            val2  += src_8_row_pointer3[6]*ker_30;
            val2  += src_8_row_pointer3[7]*ker_31;

            val3  += src_8_row_pointer4[0]*ker_24;
            val3  += src_8_row_pointer4[1]*ker_25;
            val3  += src_8_row_pointer4[2]*ker_26;
            val3  += src_8_row_pointer4[3]*ker_27;
            val3  += src_8_row_pointer4[4]*ker_28;
            val3  += src_8_row_pointer4[5]*ker_29;
            val3  += src_8_row_pointer4[6]*ker_30;
            val3  += src_8_row_pointer4[7]*ker_31;
			

            src_8_row_pointer += dim;
            src_8_row_pointer2 +=dim;
            src_8_row_pointer3 +=dim;
            src_8_row_pointer4 +=dim;

            val  += src_8_row_pointer[0]*ker_32;
            val  += src_8_row_pointer[1]*ker_33;
            val  += src_8_row_pointer[2]*ker_34;
            val  += src_8_row_pointer[3]*ker_35;
            val  += src_8_row_pointer[4]*ker_36;
            val  += src_8_row_pointer[5]*ker_37;
            val  += src_8_row_pointer[6]*ker_38;
            val  += src_8_row_pointer[7]*ker_39;

            
            val1  += src_8_row_pointer2[0]*ker_32;
            val1  += src_8_row_pointer2[1]*ker_33;
            val1  += src_8_row_pointer2[2]*ker_34;
            val1  += src_8_row_pointer2[3]*ker_35;
            val1  += src_8_row_pointer2[4]*ker_36;
            val1  += src_8_row_pointer2[5]*ker_37;
            val1  += src_8_row_pointer2[6]*ker_38;
            val1  += src_8_row_pointer2[7]*ker_39;
	
			val2  += src_8_row_pointer3[0]*ker_32;
            val2  += src_8_row_pointer3[1]*ker_33;
            val2  += src_8_row_pointer3[2]*ker_34;
            val2  += src_8_row_pointer3[3]*ker_35;
            val2  += src_8_row_pointer3[4]*ker_36;
            val2  += src_8_row_pointer3[5]*ker_37;
            val2  += src_8_row_pointer3[6]*ker_38;
            val2  += src_8_row_pointer3[7]*ker_39;

            val3  += src_8_row_pointer4[0]*ker_32;
            val3  += src_8_row_pointer4[1]*ker_33;
            val3  += src_8_row_pointer4[2]*ker_34;
            val3  += src_8_row_pointer4[3]*ker_35;
            val3  += src_8_row_pointer4[4]*ker_36;
            val3  += src_8_row_pointer4[5]*ker_37;
            val3  += src_8_row_pointer4[6]*ker_38;
            val3  += src_8_row_pointer4[7]*ker_39;


			

            src_8_row_pointer += dim;
            src_8_row_pointer2 +=dim;
            src_8_row_pointer3 +=dim;
            src_8_row_pointer4 +=dim;

            val  += src_8_row_pointer[0]*ker_40;
            val  += src_8_row_pointer[1]*ker_41;
            val  += src_8_row_pointer[2]*ker_42;
            val  += src_8_row_pointer[3]*ker_43;
            val  += src_8_row_pointer[4]*ker_44;
            val  += src_8_row_pointer[5]*ker_45;
            val  += src_8_row_pointer[6]*ker_46;
            val  += src_8_row_pointer[7]*ker_47;
            
            val1  += src_8_row_pointer2[0]*ker_40;
            val1  += src_8_row_pointer2[1]*ker_41;
            val1  += src_8_row_pointer2[2]*ker_42;
            val1  += src_8_row_pointer2[3]*ker_43;
            val1  += src_8_row_pointer2[4]*ker_44;
            val1  += src_8_row_pointer2[5]*ker_45;
            val1  += src_8_row_pointer2[6]*ker_46;
            val1  += src_8_row_pointer2[7]*ker_47;

            val2  += src_8_row_pointer3[0]*ker_40;
            val2  += src_8_row_pointer3[1]*ker_41;
            val2  += src_8_row_pointer3[2]*ker_42;
            val2  += src_8_row_pointer3[3]*ker_43;
            val2  += src_8_row_pointer3[4]*ker_44;
            val2  += src_8_row_pointer3[5]*ker_45;
            val2  += src_8_row_pointer3[6]*ker_46;
            val2  += src_8_row_pointer3[7]*ker_47;

            val3  += src_8_row_pointer4[0]*ker_40;
            val3  += src_8_row_pointer4[1]*ker_41;
            val3  += src_8_row_pointer4[2]*ker_42;
            val3  += src_8_row_pointer4[3]*ker_43;
            val3  += src_8_row_pointer4[4]*ker_44;
            val3  += src_8_row_pointer4[5]*ker_45;
            val3  += src_8_row_pointer4[6]*ker_46;
            val3  += src_8_row_pointer4[7]*ker_47;

			

            src_8_row_pointer += dim;
            src_8_row_pointer2 +=dim;
            src_8_row_pointer3 +=dim;
            src_8_row_pointer4 +=dim;

            val  += src_8_row_pointer[0]*ker_48;
            val  += src_8_row_pointer[1]*ker_49;
            val  += src_8_row_pointer[2]*ker_50;
            val  += src_8_row_pointer[3]*ker_51;
            val  += src_8_row_pointer[4]*ker_52;
            val  += src_8_row_pointer[5]*ker_53;
            val  += src_8_row_pointer[6]*ker_54;
            val  += src_8_row_pointer[7]*ker_55;
            
            val1  += src_8_row_pointer2[0]*ker_48;
            val1  += src_8_row_pointer2[1]*ker_49;
            val1  += src_8_row_pointer2[2]*ker_50;
            val1  += src_8_row_pointer2[3]*ker_51;
            val1  += src_8_row_pointer2[4]*ker_52;
            val1  += src_8_row_pointer2[5]*ker_53;
            val1  += src_8_row_pointer2[6]*ker_54;
            val1  += src_8_row_pointer2[7]*ker_55;

            val2  += src_8_row_pointer3[0]*ker_48;
            val2  += src_8_row_pointer3[1]*ker_49;
            val2  += src_8_row_pointer3[2]*ker_50;
            val2  += src_8_row_pointer3[3]*ker_51;
            val2  += src_8_row_pointer3[4]*ker_52;
            val2  += src_8_row_pointer3[5]*ker_53;
            val2  += src_8_row_pointer3[6]*ker_54;
            val2  += src_8_row_pointer3[7]*ker_55;

            val3  += src_8_row_pointer4[0]*ker_48;
            val3  += src_8_row_pointer4[1]*ker_49;
            val3  += src_8_row_pointer4[2]*ker_50;
            val3  += src_8_row_pointer4[3]*ker_51;
            val3  += src_8_row_pointer4[4]*ker_52;
            val3  += src_8_row_pointer4[5]*ker_53;
            val3  += src_8_row_pointer4[6]*ker_54;
            val3  += src_8_row_pointer4[7]*ker_55;
			
            src_8_row_pointer += dim;
            src_8_row_pointer2 +=dim;
            src_8_row_pointer3 +=dim;
            src_8_row_pointer4 +=dim;


            val  += src_8_row_pointer[0]*ker_56;
            val  += src_8_row_pointer[1]*ker_57;
            val  += src_8_row_pointer[2]*ker_58;
            val  += src_8_row_pointer[3]*ker_59;
            val  += src_8_row_pointer[4]*ker_60;
            val  += src_8_row_pointer[5]*ker_61;
            val  += src_8_row_pointer[6]*ker_62;
            val  += src_8_row_pointer[7]*ker_63;

            
            val1  += src_8_row_pointer2[0]*ker_56;
            val1  += src_8_row_pointer2[1]*ker_57;
            val1  += src_8_row_pointer2[2]*ker_58;
            val1  += src_8_row_pointer2[3]*ker_59;
            val1  += src_8_row_pointer2[4]*ker_60;
            val1  += src_8_row_pointer2[5]*ker_61;
            val1  += src_8_row_pointer2[6]*ker_62;
            val1  += src_8_row_pointer2[7]*ker_63;

            val2  += src_8_row_pointer3[0]*ker_56;
            val2  += src_8_row_pointer3[1]*ker_57;
            val2  += src_8_row_pointer3[2]*ker_58;
            val2  += src_8_row_pointer3[3]*ker_59;
            val2  += src_8_row_pointer3[4]*ker_60;
            val2  += src_8_row_pointer3[5]*ker_61;
            val2  += src_8_row_pointer3[6]*ker_62;
            val2  += src_8_row_pointer3[7]*ker_63;

            val3  += src_8_row_pointer4[0]*ker_56;
            val3  += src_8_row_pointer4[1]*ker_57;
            val3  += src_8_row_pointer4[2]*ker_58;
            val3  += src_8_row_pointer4[3]*ker_59;
            val3  += src_8_row_pointer4[4]*ker_60;
            val3  += src_8_row_pointer4[5]*ker_61;
            val3  += src_8_row_pointer4[6]*ker_62;
            val3  += src_8_row_pointer4[7]*ker_63;
			

            *dst_element_pointer = val;
            *(dst_element_pointer+1) = val1;
            *(dst_element_pointer+2) = val2;
            *(dst_element_pointer+3) = val3;
			*/
			int *src_8_row_pointer = src_element_pointer;
			val1 = val2 = val3 = val4 = 0;
			int temp_var1 = src_8_row_pointer[0];
			int temp_var2 = src_8_row_pointer[1];
			int temp_var3 = src_8_row_pointer[2];
			int temp_var4 = src_8_row_pointer[3];
			int temp_var5 = src_8_row_pointer[4];
			int temp_var6 = src_8_row_pointer[5];
			int temp_var7 = src_8_row_pointer[6];
			int temp_var8 = src_8_row_pointer[7];
			int temp_var9 = src_8_row_pointer[8];
			int temp_var10 = src_8_row_pointer[9];
			int temp_var11 = src_8_row_pointer[10];
			src_8_row_pointer += dim;
			int temp_var12 = src_8_row_pointer[0];
			int temp_var13 = src_8_row_pointer[1];
			int temp_var14 = src_8_row_pointer[2];
			int temp_var15 = src_8_row_pointer[3];
			int temp_var16 = src_8_row_pointer[4];
			int temp_var17 = src_8_row_pointer[5];
			int temp_var18 = src_8_row_pointer[6];
			int temp_var19 = src_8_row_pointer[7];
			int temp_var20 = src_8_row_pointer[8];
			int temp_var21 = src_8_row_pointer[9];
			int temp_var22 = src_8_row_pointer[10];
			src_8_row_pointer += dim;
			int temp_var23 = src_8_row_pointer[0];
			int temp_var24 = src_8_row_pointer[1];
			int temp_var25 = src_8_row_pointer[2];
			int temp_var26 = src_8_row_pointer[3];
			int temp_var27 = src_8_row_pointer[4];
			int temp_var28 = src_8_row_pointer[5];
			int temp_var29 = src_8_row_pointer[6];
			int temp_var30 = src_8_row_pointer[7];
			int temp_var31 = src_8_row_pointer[8];
			int temp_var32 = src_8_row_pointer[9];
			int temp_var33 = src_8_row_pointer[10];
			src_8_row_pointer += dim;
			int temp_var34 = src_8_row_pointer[0];
			int temp_var35 = src_8_row_pointer[1];
			int temp_var36 = src_8_row_pointer[2];
			int temp_var37 = src_8_row_pointer[3];
			int temp_var38 = src_8_row_pointer[4];
			int temp_var39 = src_8_row_pointer[5];
			int temp_var40 = src_8_row_pointer[6];
			int temp_var41 = src_8_row_pointer[7];
			int temp_var42 = src_8_row_pointer[8];
			int temp_var43 = src_8_row_pointer[9];
			int temp_var44 = src_8_row_pointer[10];
			src_8_row_pointer += dim;
			int temp_var45 = src_8_row_pointer[0];
			int temp_var46 = src_8_row_pointer[1];
			int temp_var47 = src_8_row_pointer[2];
			int temp_var48 = src_8_row_pointer[3];
			int temp_var49 = src_8_row_pointer[4];
			int temp_var50 = src_8_row_pointer[5];
			int temp_var51 = src_8_row_pointer[6];
			int temp_var52 = src_8_row_pointer[7];
			int temp_var53 = src_8_row_pointer[8];
			int temp_var54 = src_8_row_pointer[9];
			int temp_var55 = src_8_row_pointer[10];
			src_8_row_pointer += dim;
			int temp_var56 = src_8_row_pointer[0];
			int temp_var57 = src_8_row_pointer[1];
			int temp_var58 = src_8_row_pointer[2];
			int temp_var59 = src_8_row_pointer[3];
			int temp_var60 = src_8_row_pointer[4];
			int temp_var61 = src_8_row_pointer[5];
			int temp_var62 = src_8_row_pointer[6];
			int temp_var63 = src_8_row_pointer[7];
			int temp_var64 = src_8_row_pointer[8];
			int temp_var65 = src_8_row_pointer[9];
			int temp_var66 = src_8_row_pointer[10];
			src_8_row_pointer += dim;
			int temp_var67 = src_8_row_pointer[0];
			int temp_var68 = src_8_row_pointer[1];
			int temp_var69 = src_8_row_pointer[2];
			int temp_var70 = src_8_row_pointer[3];
			int temp_var71 = src_8_row_pointer[4];
			int temp_var72 = src_8_row_pointer[5];
			int temp_var73 = src_8_row_pointer[6];
			int temp_var74 = src_8_row_pointer[7];
			int temp_var75 = src_8_row_pointer[8];
			int temp_var76 = src_8_row_pointer[9];
			int temp_var77 = src_8_row_pointer[10];
			src_8_row_pointer += dim;
			int temp_var78 = src_8_row_pointer[0];
			int temp_var79 = src_8_row_pointer[1];
			int temp_var80 = src_8_row_pointer[2];
			int temp_var81 = src_8_row_pointer[3];
			int temp_var82 = src_8_row_pointer[4];
			int temp_var83 = src_8_row_pointer[5];
			int temp_var84 = src_8_row_pointer[6];
			int temp_var85 = src_8_row_pointer[7];
			int temp_var86 = src_8_row_pointer[8];
			int temp_var87 = src_8_row_pointer[9];
			int temp_var88 = src_8_row_pointer[10];

			val1 += temp_var1* ker_0;
			val1 += temp_var2* ker_1;
			val1 += temp_var3* ker_2;
			val1 += temp_var4* ker_3;
			val1 += temp_var5* ker_4;
			val1 += temp_var6* ker_5;
			val1 += temp_var7* ker_6;
			val1 += temp_var8* ker_7;
			val1 += temp_var12* ker_8;
			val1 += temp_var13* ker_9;
			val1 += temp_var14* ker_10;
			val1 += temp_var15* ker_11;
			val1 += temp_var16* ker_12;
			val1 += temp_var17* ker_13;
			val1 += temp_var18* ker_14;
			val1 += temp_var19* ker_15;
			val1 += temp_var23* ker_16;
			val1 += temp_var24* ker_17;
			val1 += temp_var25* ker_18;
			val1 += temp_var26* ker_19;
			val1 += temp_var27* ker_20;
			val1 += temp_var28* ker_21;
			val1 += temp_var29* ker_22;
			val1 += temp_var30* ker_23;
			val1 += temp_var34* ker_24;
			val1 += temp_var35* ker_25;
			val1 += temp_var36* ker_26;
			val1 += temp_var37* ker_27;
			val1 += temp_var38* ker_28;
			val1 += temp_var39* ker_29;
			val1 += temp_var40* ker_30;
			val1 += temp_var41* ker_31;
			val1 += temp_var45* ker_32;
			val1 += temp_var46* ker_33;
			val1 += temp_var47* ker_34;
			val1 += temp_var48* ker_35;
			val1 += temp_var49* ker_36;
			val1 += temp_var50* ker_37;
			val1 += temp_var51* ker_38;
			val1 += temp_var52* ker_39;
			val1 += temp_var56* ker_40;
			val1 += temp_var57* ker_41;
			val1 += temp_var58* ker_42;
			val1 += temp_var59* ker_43;
			val1 += temp_var60* ker_44;
			val1 += temp_var61* ker_45;
			val1 += temp_var62* ker_46;
			val1 += temp_var63* ker_47;
			val1 += temp_var67* ker_48;
			val1 += temp_var68* ker_49;
			val1 += temp_var69* ker_50;
			val1 += temp_var70* ker_51;
			val1 += temp_var71* ker_52;
			val1 += temp_var72* ker_53;
			val1 += temp_var73* ker_54;
			val1 += temp_var74* ker_55;
			val1 += temp_var78* ker_56;
			val1 += temp_var79* ker_57;
			val1 += temp_var80* ker_58;
			val1 += temp_var81* ker_59;
			val1 += temp_var82* ker_60;
			val1 += temp_var83* ker_61;
			val1 += temp_var84* ker_62;
			val1 += temp_var85* ker_63;




			val2 += temp_var2* ker_0;
			val2 += temp_var3* ker_1;
			val2 += temp_var4* ker_2;
			val2 += temp_var5* ker_3;
			val2 += temp_var6* ker_4;
			val2 += temp_var7* ker_5;
			val2 += temp_var8* ker_6;
			val2 += temp_var9* ker_7;
			val2 += temp_var13* ker_8;
			val2 += temp_var14* ker_9;
			val2 += temp_var15* ker_10;
			val2 += temp_var16* ker_11;
			val2 += temp_var17* ker_12;
			val2 += temp_var18* ker_13;
			val2 += temp_var19* ker_14;
			val2 += temp_var20* ker_15;
			val2 += temp_var24* ker_16;
			val2 += temp_var25* ker_17;
			val2 += temp_var26* ker_18;
			val2 += temp_var27* ker_19;
			val2 += temp_var28* ker_20;
			val2 += temp_var29* ker_21;
			val2 += temp_var30* ker_22;
			val2 += temp_var31* ker_23;
			val2 += temp_var35* ker_24;
			val2 += temp_var36* ker_25;
			val2 += temp_var37* ker_26;
			val2 += temp_var38* ker_27;
			val2 += temp_var39* ker_28;
			val2 += temp_var40* ker_29;
			val2 += temp_var41* ker_30;
			val2 += temp_var42* ker_31;
			val2 += temp_var46* ker_32;
			val2 += temp_var47* ker_33;
			val2 += temp_var48* ker_34;
			val2 += temp_var49* ker_35;
			val2 += temp_var50* ker_36;
			val2 += temp_var51* ker_37;
			val2 += temp_var52* ker_38;
			val2 += temp_var53* ker_39;
			val2 += temp_var57* ker_40;
			val2 += temp_var58* ker_41;
			val2 += temp_var59* ker_42;
			val2 += temp_var60* ker_43;
			val2 += temp_var61* ker_44;
			val2 += temp_var62* ker_45;
			val2 += temp_var63* ker_46;
			val2 += temp_var64* ker_47;
			val2 += temp_var68* ker_48;
			val2 += temp_var69* ker_49;
			val2 += temp_var70* ker_50;
			val2 += temp_var71* ker_51;
			val2 += temp_var72* ker_52;
			val2 += temp_var73* ker_53;
			val2 += temp_var74* ker_54;
			val2 += temp_var75* ker_55;
			val2 += temp_var79* ker_56;
			val2 += temp_var80* ker_57;
			val2 += temp_var81* ker_58;
			val2 += temp_var82* ker_59;
			val2 += temp_var83* ker_60;
			val2 += temp_var84* ker_61;
			val2 += temp_var85* ker_62;
			val2 += temp_var86* ker_63;


			val3 += temp_var3* ker_0;
			val3 += temp_var4* ker_1;
			val3 += temp_var5* ker_2;
			val3 += temp_var6* ker_3;
			val3 += temp_var7* ker_4;
			val3 += temp_var8* ker_5;
			val3 += temp_var9* ker_6;
			val3 += temp_var10* ker_7;
			val3 += temp_var14* ker_8;
			val3 += temp_var15* ker_9;
			val3 += temp_var16* ker_10;
			val3 += temp_var17* ker_11;
			val3 += temp_var18* ker_12;
			val3 += temp_var19* ker_13;
			val3 += temp_var20* ker_14;
			val3 += temp_var21* ker_15;
			val3 += temp_var25* ker_16;
			val3 += temp_var26* ker_17;
			val3 += temp_var27* ker_18;
			val3 += temp_var28* ker_19;
			val3 += temp_var29* ker_20;
			val3 += temp_var30* ker_21;
			val3 += temp_var31* ker_22;
			val3 += temp_var32* ker_23;
			val3 += temp_var36* ker_24;
			val3 += temp_var37* ker_25;
			val3 += temp_var38* ker_26;
			val3 += temp_var39* ker_27;
			val3 += temp_var40* ker_28;
			val3 += temp_var41* ker_29;
			val3 += temp_var42* ker_30;
			val3 += temp_var43* ker_31;
			val3 += temp_var47* ker_32;
			val3 += temp_var48* ker_33;
			val3 += temp_var49* ker_34;
			val3 += temp_var50* ker_35;
			val3 += temp_var51* ker_36;
			val3 += temp_var52* ker_37;
			val3 += temp_var53* ker_38;
			val3 += temp_var54* ker_39;
			val3 += temp_var58* ker_40;
			val3 += temp_var59* ker_41;
			val3 += temp_var60* ker_42;
			val3 += temp_var61* ker_43;
			val3 += temp_var62* ker_44;
			val3 += temp_var63* ker_45;
			val3 += temp_var64* ker_46;
			val3 += temp_var65* ker_47;
			val3 += temp_var69* ker_48;
			val3 += temp_var70* ker_49;
			val3 += temp_var71* ker_50;
			val3 += temp_var72* ker_51;
			val3 += temp_var73* ker_52;
			val3 += temp_var74* ker_53;
			val3 += temp_var75* ker_54;
			val3 += temp_var76* ker_55;
			val3 += temp_var80* ker_56;
			val3 += temp_var81* ker_57;
			val3 += temp_var82* ker_58;
			val3 += temp_var83* ker_59;
			val3 += temp_var84* ker_60;
			val3 += temp_var85* ker_61;
			val3 += temp_var86* ker_62;
			val3 += temp_var87* ker_63;

			val4 += temp_var4* ker_0;
			val4 += temp_var5* ker_1;
			val4 += temp_var6* ker_2;
			val4 += temp_var7* ker_3;
			val4 += temp_var8* ker_4;
			val4 += temp_var9* ker_5;
			val4 += temp_var10* ker_6;
			val4 += temp_var11* ker_7;
			val4 += temp_var15* ker_8;
			val4 += temp_var16* ker_9;
			val4 += temp_var17* ker_10;
			val4 += temp_var18* ker_11;
			val4 += temp_var19* ker_12;
			val4 += temp_var20* ker_13;
			val4 += temp_var21* ker_14;
			val4 += temp_var22* ker_15;
			val4 += temp_var26* ker_16;
			val4 += temp_var27* ker_17;
			val4 += temp_var28* ker_18;
			val4 += temp_var29* ker_19;
			val4 += temp_var30* ker_20;
			val4 += temp_var31* ker_21;
			val4 += temp_var32* ker_22;
			val4 += temp_var33* ker_23;
			val4 += temp_var37* ker_24;
			val4 += temp_var38* ker_25;
			val4 += temp_var39* ker_26;
			val4 += temp_var40* ker_27;
			val4 += temp_var41* ker_28;
			val4 += temp_var42* ker_29;
			val4 += temp_var43* ker_30;
			val4 += temp_var44* ker_31;
			val4 += temp_var48* ker_32;
			val4 += temp_var49* ker_33;
			val4 += temp_var50* ker_34;
			val4 += temp_var51* ker_35;
			val4 += temp_var52* ker_36;
			val4 += temp_var53* ker_37;
			val4 += temp_var54* ker_38;
			val4 += temp_var55* ker_39;
			val4 += temp_var59* ker_40;
			val4 += temp_var60* ker_41;
			val4 += temp_var61* ker_42;
			val4 += temp_var62* ker_43;
			val4 += temp_var63* ker_44;
			val4 += temp_var64* ker_45;
			val4 += temp_var65* ker_46;
			val4 += temp_var66* ker_47;
			val4 += temp_var70* ker_48;
			val4 += temp_var71* ker_49;
			val4 += temp_var72* ker_50;
			val4 += temp_var73* ker_51;
			val4 += temp_var74* ker_52;
			val4 += temp_var75* ker_53;
			val4 += temp_var76* ker_54;
			val4 += temp_var77* ker_55;
			val4 += temp_var81* ker_56;
			val4 += temp_var82* ker_57;
			val4 += temp_var83* ker_58;
			val4 += temp_var84* ker_59;
			val4 += temp_var85* ker_60;
			val4 += temp_var86* ker_61;
			val4 += temp_var87* ker_62;
			val4 += temp_var88* ker_63;

			*dst_element_pointer = val1;
            *(dst_element_pointer+1) = val2;
            *(dst_element_pointer+2) = val3;
            *(dst_element_pointer+3) = val4;

        }

    }

}

/* 
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Dot product: Current working version";
void convolution(int dim,int *src, int *ker,int *dst) 
{

        convo(dim,src,ker,dst);

}

/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_conv_functions() {
    add_conv_function(&naive_conv, naive_conv_descr);   
    add_conv_function(&convolution, convolution_descr);   
    /* ... Register additional test functions here */
}




/***************
 * MATRIX MULTIP KERNEL
 ***************/

/******************************************************
 * Your different versions of the matrix multiplications  go here
 ******************************************************/

/* 
 * naive_matrix_multiplication - The naive baseline version of matrix multiplication 
 */
char naive_matrix_multiplication_descr[] =
    "Naive_matrix_multiplication: Naive baseline implementation";
void naive_matrix_multiplication(int dim,int *src, int *src2,int *dst) {
    int i,j,k;

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++) {
            dst[j*dim+i]=0;
            for(k = 0; k < dim; k++) 
            dst[j*dim+i] = dst[j*dim+i] + src[j*dim+k]*src2[i+k*dim];
        }    
}

char matmulo_descr[] = "matmulo";
void matmulo(int dim, int *src, int *src2,int *dst) 
{
    int r;
    int row_count,row_index;

    int* dst_element_pointer;
    int* src2_row_pointer;
    int* src_row_element_pointer;
    int row_index_element_index;
    if (dim > 64){

    int dim2 = dim * dim;
    dst_element_pointer = dst;
    int q;
    for(q = 0; q < dim2; q += 64){
        dst_element_pointer[0] = dst_element_pointer[1] = dst_element_pointer[2] = dst_element_pointer[3] = 0;
        dst_element_pointer[4] = dst_element_pointer[5] = dst_element_pointer[6] = dst_element_pointer[7] = 0;
        dst_element_pointer[8] = dst_element_pointer[9] = dst_element_pointer[10] = dst_element_pointer[11] = 0;
        dst_element_pointer[12] = dst_element_pointer[13] = dst_element_pointer[14] = dst_element_pointer[15] = 0;
        dst_element_pointer[16] = dst_element_pointer[17] = dst_element_pointer[18] = dst_element_pointer[19] = 0;
        dst_element_pointer[20] = dst_element_pointer[21] = dst_element_pointer[22] = dst_element_pointer[23] = 0;
        dst_element_pointer[24] = dst_element_pointer[25] = dst_element_pointer[26] = dst_element_pointer[27] = 0;
        dst_element_pointer[28] = dst_element_pointer[29] = dst_element_pointer[30] = dst_element_pointer[31] = 0;
        dst_element_pointer += 32;
        dst_element_pointer[0] = dst_element_pointer[1] = dst_element_pointer[2] = dst_element_pointer[3] = 0;
        dst_element_pointer[4] = dst_element_pointer[5] = dst_element_pointer[6] = dst_element_pointer[7] = 0;
        dst_element_pointer[8] = dst_element_pointer[9] = dst_element_pointer[10] = dst_element_pointer[11] = 0;
        dst_element_pointer[12] = dst_element_pointer[13] = dst_element_pointer[14] = dst_element_pointer[15] = 0;
        dst_element_pointer[16] = dst_element_pointer[17] = dst_element_pointer[18] = dst_element_pointer[19] = 0;
        dst_element_pointer[20] = dst_element_pointer[21] = dst_element_pointer[22] = dst_element_pointer[23] = 0;
        dst_element_pointer[24] = dst_element_pointer[25] = dst_element_pointer[26] = dst_element_pointer[27] = 0;
        dst_element_pointer[28] = dst_element_pointer[29] = dst_element_pointer[30] = dst_element_pointer[31] = 0;
        dst_element_pointer += 32;
    }

    for(row_index=0; row_index < dim * dim; row_index=row_index_element_index){
        row_index_element_index = row_index + dim;
        
            for(src_row_element_pointer = src+row_index, row_count=0; src_row_element_pointer < src+row_index_element_index; src_row_element_pointer++, row_count +=dim) {
                r = *(src_row_element_pointer);
                dst_element_pointer = dst + row_index;
                src2_row_pointer = src2 + row_count;
                for(dst_element_pointer = dst + row_index, src2_row_pointer = src2 + row_count; dst_element_pointer < dst+row_index_element_index; dst_element_pointer += 16, src2_row_pointer += 16) {
                    dst_element_pointer[0] += r * src2_row_pointer[0];
                    dst_element_pointer[1] += r * src2_row_pointer[1];
                    dst_element_pointer[2] += r * src2_row_pointer[2];
                    dst_element_pointer[3] += r * src2_row_pointer[3];
                    dst_element_pointer[4] += r * src2_row_pointer[4];
                    dst_element_pointer[5] += r * src2_row_pointer[5];
                    dst_element_pointer[6] += r * src2_row_pointer[6];
                    dst_element_pointer[7] += r * src2_row_pointer[7];
                    dst_element_pointer[8] += r * src2_row_pointer[8];
                    dst_element_pointer[9] += r * src2_row_pointer[9];
                    dst_element_pointer[10] += r * src2_row_pointer[10];
                    dst_element_pointer[11] += r * src2_row_pointer[11];
                    dst_element_pointer[12] += r * src2_row_pointer[12];
                    dst_element_pointer[13] += r * src2_row_pointer[13];
                    dst_element_pointer[14] += r * src2_row_pointer[14];
                    dst_element_pointer[15] += r * src2_row_pointer[15];
                    dst_element_pointer += 16;
                    src2_row_pointer += 16;
                    dst_element_pointer[0] += r * src2_row_pointer[0];
                    dst_element_pointer[1] += r * src2_row_pointer[1];
                    dst_element_pointer[2] += r * src2_row_pointer[2];
                    dst_element_pointer[3] += r * src2_row_pointer[3];
                    dst_element_pointer[4] += r * src2_row_pointer[4];
                    dst_element_pointer[5] += r * src2_row_pointer[5];
                    dst_element_pointer[6] += r * src2_row_pointer[6];
                    dst_element_pointer[7] += r * src2_row_pointer[7];
                    dst_element_pointer[8] += r * src2_row_pointer[8];
                    dst_element_pointer[9] += r * src2_row_pointer[9];
                    dst_element_pointer[10] += r * src2_row_pointer[10];
                    dst_element_pointer[11] += r * src2_row_pointer[11];
                    dst_element_pointer[12] += r * src2_row_pointer[12];
                    dst_element_pointer[13] += r * src2_row_pointer[13];
                    dst_element_pointer[14] += r * src2_row_pointer[14];
                    dst_element_pointer[15] += r * src2_row_pointer[15];

                }
            }

    
        }
    }
    if(dim == 64){
        int element_index_inside = 0,i;
        i = 64;
        while(i--){
            int r  = src[element_index_inside];
            int *dst_element_pointer  = dst+element_index_inside;
            int * src2_pointer = src2;
            dst_element_pointer[0 ] = r * src2_pointer[0 ];
            dst_element_pointer[1 ] = r * src2_pointer[1 ];
            dst_element_pointer[2 ] = r * src2_pointer[2 ];
            dst_element_pointer[3 ] = r * src2_pointer[3 ];
            dst_element_pointer[4 ] = r * src2_pointer[4 ];
            dst_element_pointer[5 ] = r * src2_pointer[5 ];
            dst_element_pointer[6 ] = r * src2_pointer[6 ];
            dst_element_pointer[7 ] = r * src2_pointer[7 ];
            dst_element_pointer[8 ] = r * src2_pointer[8 ];
            dst_element_pointer[9 ] = r * src2_pointer[9 ];
            dst_element_pointer[10] = r * src2_pointer[10];
            dst_element_pointer[11] = r * src2_pointer[11];
            dst_element_pointer[12] = r * src2_pointer[12];
            dst_element_pointer[13] = r * src2_pointer[13];
            dst_element_pointer[14] = r * src2_pointer[14];
            dst_element_pointer[15] = r * src2_pointer[15];
            dst_element_pointer += 16;
            src2_pointer += 16;
            dst_element_pointer[0 ] = r * src2_pointer[0 ];
            dst_element_pointer[1 ] = r * src2_pointer[1 ];
            dst_element_pointer[2 ] = r * src2_pointer[2 ];
            dst_element_pointer[3 ] = r * src2_pointer[3 ];
            dst_element_pointer[4 ] = r * src2_pointer[4 ];
            dst_element_pointer[5 ] = r * src2_pointer[5 ];
            dst_element_pointer[6 ] = r * src2_pointer[6 ];
            dst_element_pointer[7 ] = r * src2_pointer[7 ];
            dst_element_pointer[8 ] = r * src2_pointer[8 ];
            dst_element_pointer[9 ] = r * src2_pointer[9 ];
            dst_element_pointer[10] = r * src2_pointer[10];
            dst_element_pointer[11] = r * src2_pointer[11];
            dst_element_pointer[12] = r * src2_pointer[12];
            dst_element_pointer[13] = r * src2_pointer[13];
            dst_element_pointer[14] = r * src2_pointer[14];
            dst_element_pointer[15] = r * src2_pointer[15];
            dst_element_pointer += 16;
            src2_pointer += 16;
            dst_element_pointer[0 ] = r * src2_pointer[0 ];
            dst_element_pointer[1 ] = r * src2_pointer[1 ];
            dst_element_pointer[2 ] = r * src2_pointer[2 ];
            dst_element_pointer[3 ] = r * src2_pointer[3 ];
            dst_element_pointer[4 ] = r * src2_pointer[4 ];
            dst_element_pointer[5 ] = r * src2_pointer[5 ];
            dst_element_pointer[6 ] = r * src2_pointer[6 ];
            dst_element_pointer[7 ] = r * src2_pointer[7 ];
            dst_element_pointer[8 ] = r * src2_pointer[8 ];
            dst_element_pointer[9 ] = r * src2_pointer[9 ];
            dst_element_pointer[10] = r * src2_pointer[10];
            dst_element_pointer[11] = r * src2_pointer[11];
            dst_element_pointer[12] = r * src2_pointer[12];
            dst_element_pointer[13] = r * src2_pointer[13];
            dst_element_pointer[14] = r * src2_pointer[14];
            dst_element_pointer[15] = r * src2_pointer[15];
            dst_element_pointer += 16;
            src2_pointer += 16;
            dst_element_pointer[0 ] = r * src2_pointer[0 ];
            dst_element_pointer[1 ] = r * src2_pointer[1 ];
            dst_element_pointer[2 ] = r * src2_pointer[2 ];
            dst_element_pointer[3 ] = r * src2_pointer[3 ];
            dst_element_pointer[4 ] = r * src2_pointer[4 ];
            dst_element_pointer[5 ] = r * src2_pointer[5 ];
            dst_element_pointer[6 ] = r * src2_pointer[6 ];
            dst_element_pointer[7 ] = r * src2_pointer[7 ];
            dst_element_pointer[8 ] = r * src2_pointer[8 ];
            dst_element_pointer[9 ] = r * src2_pointer[9 ];
            dst_element_pointer[10] = r * src2_pointer[10];
            dst_element_pointer[11] = r * src2_pointer[11];
            dst_element_pointer[12] = r * src2_pointer[12];
            dst_element_pointer[13] = r * src2_pointer[13];
            dst_element_pointer[14] = r * src2_pointer[14];
            dst_element_pointer[15] = r * src2_pointer[15];
            element_index_inside += 64;
        }

        int element_index = 64;
        for (int k = 1; k < 64; k++) {
            int element_index_inside = 0;
            int *src2_row_pointer = src2 + element_index;
            i = 64;
            while(i--) {
                int r  = src[element_index_inside+k];
                int *dst_element_pointer  = dst+element_index_inside;
                int * pointer_src2_row_pointer = src2_row_pointer;
                dst_element_pointer[0 ] += r * pointer_src2_row_pointer[0 ];
                dst_element_pointer[1 ] += r * pointer_src2_row_pointer[1 ];
                dst_element_pointer[2 ] += r * pointer_src2_row_pointer[2 ];
                dst_element_pointer[3 ] += r * pointer_src2_row_pointer[3 ];
                dst_element_pointer[4 ] += r * pointer_src2_row_pointer[4 ];
                dst_element_pointer[5 ] += r * pointer_src2_row_pointer[5 ];
                dst_element_pointer[6 ] += r * pointer_src2_row_pointer[6 ];
                dst_element_pointer[7 ] += r * pointer_src2_row_pointer[7 ];
                dst_element_pointer[8 ] += r * pointer_src2_row_pointer[8 ];
                dst_element_pointer[9 ] += r * pointer_src2_row_pointer[9 ];
                dst_element_pointer[10] += r * pointer_src2_row_pointer[10];
                dst_element_pointer[11] += r * pointer_src2_row_pointer[11];
                dst_element_pointer[12] += r * pointer_src2_row_pointer[12];
                dst_element_pointer[13] += r * pointer_src2_row_pointer[13];
                dst_element_pointer[14] += r * pointer_src2_row_pointer[14];
                dst_element_pointer[15] += r * pointer_src2_row_pointer[15];
                dst_element_pointer += 16;
                pointer_src2_row_pointer += 16;
                dst_element_pointer[0 ] += r * pointer_src2_row_pointer[0 ];
                dst_element_pointer[1 ] += r * pointer_src2_row_pointer[1 ];
                dst_element_pointer[2 ] += r * pointer_src2_row_pointer[2 ];
                dst_element_pointer[3 ] += r * pointer_src2_row_pointer[3 ];
                dst_element_pointer[4 ] += r * pointer_src2_row_pointer[4 ];
                dst_element_pointer[5 ] += r * pointer_src2_row_pointer[5 ];
                dst_element_pointer[6 ] += r * pointer_src2_row_pointer[6 ];
                dst_element_pointer[7 ] += r * pointer_src2_row_pointer[7 ];
                dst_element_pointer[8 ] += r * pointer_src2_row_pointer[8 ];
                dst_element_pointer[9 ] += r * pointer_src2_row_pointer[9 ];
                dst_element_pointer[10] += r * pointer_src2_row_pointer[10];
                dst_element_pointer[11] += r * pointer_src2_row_pointer[11];
                dst_element_pointer[12] += r * pointer_src2_row_pointer[12];
                dst_element_pointer[13] += r * pointer_src2_row_pointer[13];
                dst_element_pointer[14] += r * pointer_src2_row_pointer[14];
                dst_element_pointer[15] += r * pointer_src2_row_pointer[15];
                dst_element_pointer += 16;
                pointer_src2_row_pointer += 16;
                dst_element_pointer[0 ] += r * pointer_src2_row_pointer[0 ];
                dst_element_pointer[1 ] += r * pointer_src2_row_pointer[1 ];
                dst_element_pointer[2 ] += r * pointer_src2_row_pointer[2 ];
                dst_element_pointer[3 ] += r * pointer_src2_row_pointer[3 ];
                dst_element_pointer[4 ] += r * pointer_src2_row_pointer[4 ];
                dst_element_pointer[5 ] += r * pointer_src2_row_pointer[5 ];
                dst_element_pointer[6 ] += r * pointer_src2_row_pointer[6 ];
                dst_element_pointer[7 ] += r * pointer_src2_row_pointer[7 ];
                dst_element_pointer[8 ] += r * pointer_src2_row_pointer[8 ];
                dst_element_pointer[9 ] += r * pointer_src2_row_pointer[9 ];
                dst_element_pointer[10] += r * pointer_src2_row_pointer[10];
                dst_element_pointer[11] += r * pointer_src2_row_pointer[11];
                dst_element_pointer[12] += r * pointer_src2_row_pointer[12];
                dst_element_pointer[13] += r * pointer_src2_row_pointer[13];
                dst_element_pointer[14] += r * pointer_src2_row_pointer[14];
                dst_element_pointer[15] += r * pointer_src2_row_pointer[15];
                dst_element_pointer += 16;
                pointer_src2_row_pointer += 16;
                dst_element_pointer[0 ] += r * pointer_src2_row_pointer[0 ];
                dst_element_pointer[1 ] += r * pointer_src2_row_pointer[1 ];
                dst_element_pointer[2 ] += r * pointer_src2_row_pointer[2 ];
                dst_element_pointer[3 ] += r * pointer_src2_row_pointer[3 ];
                dst_element_pointer[4 ] += r * pointer_src2_row_pointer[4 ];
                dst_element_pointer[5 ] += r * pointer_src2_row_pointer[5 ];
                dst_element_pointer[6 ] += r * pointer_src2_row_pointer[6 ];
                dst_element_pointer[7 ] += r * pointer_src2_row_pointer[7 ];
                dst_element_pointer[8 ] += r * pointer_src2_row_pointer[8 ];
                dst_element_pointer[9 ] += r * pointer_src2_row_pointer[9 ];
                dst_element_pointer[10] += r * pointer_src2_row_pointer[10];
                dst_element_pointer[11] += r * pointer_src2_row_pointer[11];
                dst_element_pointer[12] += r * pointer_src2_row_pointer[12];
                dst_element_pointer[13] += r * pointer_src2_row_pointer[13];
                dst_element_pointer[14] += r * pointer_src2_row_pointer[14];
                dst_element_pointer[15] += r * pointer_src2_row_pointer[15];

                element_index_inside += 64;
            }
            element_index += 64;
        }
    }
    if(dim == 32){
        int element_index_inside = 0;
        for (int i = 32; i-- ; ) {
            int r  = src[element_index_inside];
            int *dst_element_pointer  = dst+element_index_inside;
            int *src2_pointer = src2;
            dst_element_pointer[0 ] = r * src2_pointer[0 ];
            dst_element_pointer[1 ] = r * src2_pointer[1 ];
            dst_element_pointer[2 ] = r * src2_pointer[2 ];
            dst_element_pointer[3 ] = r * src2_pointer[3 ];
            dst_element_pointer[4 ] = r * src2_pointer[4 ];
            dst_element_pointer[5 ] = r * src2_pointer[5 ];
            dst_element_pointer[6 ] = r * src2_pointer[6 ];
            dst_element_pointer[7 ] = r * src2_pointer[7 ];
            dst_element_pointer[8 ] = r * src2_pointer[8 ];
            dst_element_pointer[9 ] = r * src2_pointer[9 ];
            dst_element_pointer[10] = r * src2_pointer[10];
            dst_element_pointer[11] = r * src2_pointer[11];
            dst_element_pointer[12] = r * src2_pointer[12];
            dst_element_pointer[13] = r * src2_pointer[13];
            dst_element_pointer[14] = r * src2_pointer[14];
            dst_element_pointer[15] = r * src2_pointer[15];
            dst_element_pointer += 16;
            src2_pointer += 16;
            dst_element_pointer[0 ] = r * src2_pointer[0 ];
            dst_element_pointer[1 ] = r * src2_pointer[1 ];
            dst_element_pointer[2 ] = r * src2_pointer[2 ];
            dst_element_pointer[3 ] = r * src2_pointer[3 ];
            dst_element_pointer[4 ] = r * src2_pointer[4 ];
            dst_element_pointer[5 ] = r * src2_pointer[5 ];
            dst_element_pointer[6 ] = r * src2_pointer[6 ];
            dst_element_pointer[7 ] = r * src2_pointer[7 ];
            dst_element_pointer[8 ] = r * src2_pointer[8 ];
            dst_element_pointer[9 ] = r * src2_pointer[9 ];
            dst_element_pointer[10] = r * src2_pointer[10];
            dst_element_pointer[11] = r * src2_pointer[11];
            dst_element_pointer[12] = r * src2_pointer[12];
            dst_element_pointer[13] = r * src2_pointer[13];
            dst_element_pointer[14] = r * src2_pointer[14];
            dst_element_pointer[15] = r * src2_pointer[15];
            element_index_inside += 32;
        }

        int element_index = 32;
        for (int k = 1; k < 32; k++) {
            int element_index_inside = 0;
            int *src2_row_pointer = src2 + element_index;
            for (int i = 32; i--;) {
                int r  = src[element_index_inside+k];
                int *dst_element_pointer  = dst+element_index_inside;
                int * pointer_src2_row_pointer = src2_row_pointer;
                dst_element_pointer[0 ] += r * pointer_src2_row_pointer[0 ];
                dst_element_pointer[1 ] += r * pointer_src2_row_pointer[1 ];
                dst_element_pointer[2 ] += r * pointer_src2_row_pointer[2 ];
                dst_element_pointer[3 ] += r * pointer_src2_row_pointer[3 ];
                dst_element_pointer[4 ] += r * pointer_src2_row_pointer[4 ];
                dst_element_pointer[5 ] += r * pointer_src2_row_pointer[5 ];
                dst_element_pointer[6 ] += r * pointer_src2_row_pointer[6 ];
                dst_element_pointer[7 ] += r * pointer_src2_row_pointer[7 ];
                dst_element_pointer[8 ] += r * pointer_src2_row_pointer[8 ];
                dst_element_pointer[9 ] += r * pointer_src2_row_pointer[9 ];
                dst_element_pointer[10] += r * pointer_src2_row_pointer[10];
                dst_element_pointer[11] += r * pointer_src2_row_pointer[11];
                dst_element_pointer[12] += r * pointer_src2_row_pointer[12];
                dst_element_pointer[13] += r * pointer_src2_row_pointer[13];
                dst_element_pointer[14] += r * pointer_src2_row_pointer[14];
                dst_element_pointer[15] += r * pointer_src2_row_pointer[15];
                dst_element_pointer += 16;
                pointer_src2_row_pointer += 16;
                dst_element_pointer[0 ] += r * pointer_src2_row_pointer[0 ];
                dst_element_pointer[1 ] += r * pointer_src2_row_pointer[1 ];
                dst_element_pointer[2 ] += r * pointer_src2_row_pointer[2 ];
                dst_element_pointer[3 ] += r * pointer_src2_row_pointer[3 ];
                dst_element_pointer[4 ] += r * pointer_src2_row_pointer[4 ];
                dst_element_pointer[5 ] += r * pointer_src2_row_pointer[5 ];
                dst_element_pointer[6 ] += r * pointer_src2_row_pointer[6 ];
                dst_element_pointer[7 ] += r * pointer_src2_row_pointer[7 ];
                dst_element_pointer[8 ] += r * pointer_src2_row_pointer[8 ];
                dst_element_pointer[9 ] += r * pointer_src2_row_pointer[9 ];
                dst_element_pointer[10] += r * pointer_src2_row_pointer[10];
                dst_element_pointer[11] += r * pointer_src2_row_pointer[11];
                dst_element_pointer[12] += r * pointer_src2_row_pointer[12];
                dst_element_pointer[13] += r * pointer_src2_row_pointer[13];
                dst_element_pointer[14] += r * pointer_src2_row_pointer[14];
                dst_element_pointer[15] += r * pointer_src2_row_pointer[15];
                
                element_index_inside += 32;
            }
            element_index += 32;
        }
    }
}

/* 
 * matrix_multiplication - Your current working version of matrix_multiplication
 * IMPORTANT: This is the version you will be graded on
 */
char matrix_multiplication_descr[] = "Matrix multiplications: Current working version";
void matrix_multiplication(int dim,int *src, int *src2,int *dst) 
{
    matmulo(dim,src,src2,dst);
}

/*********************************************************************
 * register_matrix_multiplication_functions - Register all of your different versions
 *     of the matrix multiplication  with the driver by calling the
 *     add_matrix_multiplication_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_matrix_multiplication_functions() {
    add_matrix_multiplication_function(&naive_matrix_multiplication,
        naive_matrix_multiplication_descr);   
    add_matrix_multiplication_function(&matrix_multiplication,
        matrix_multiplication_descr);   
    /* ... Register additional test functions here */
}



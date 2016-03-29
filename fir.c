#include "fir.h"

void fir(DataBuffer* dataBuffer, float* acRFiltre, float* acIRFiltre){
	float hk[51] = {
	1.4774946e-019,
	1.6465231e-004,
	3.8503956e-004,
	7.0848037e-004,
	1.1840522e-003,
	1.8598621e-003,
	2.7802151e-003,
	3.9828263e-003,
	5.4962252e-003,
	7.3374938e-003,
	9.5104679e-003,
	1.2004510e-002,
	1.4793934e-002,
	1.7838135e-002,
	2.1082435e-002,
	2.4459630e-002,
	2.7892178e-002,
	3.1294938e-002,
	3.4578348e-002,
	3.7651889e-002,
	4.0427695e-002,
	4.2824111e-002,
	4.4769071e-002,
	4.6203098e-002,
	4.7081811e-002,
	4.7377805e-002,
	4.7081811e-002,
	4.6203098e-002,
	4.4769071e-002,
	4.2824111e-002,
	4.0427695e-002,
	3.7651889e-002,
	3.4578348e-002,
	3.1294938e-002,
	2.7892178e-002,
	2.4459630e-002,
	2.1082435e-002,
	1.7838135e-002,
	1.4793934e-002,
	1.2004510e-002,
	9.5104679e-003,
	7.3374938e-003,
	5.4962252e-003,
	3.9828263e-003,
	2.7802151e-003,
	1.8598621e-003,
	1.1840522e-003,
	7.0848037e-004,
	3.8503956e-004,
	1.6465231e-004,
	1.4774946e-019
};
	int i;

	*acRFiltre = 0;
	*acIRFiltre = 0;

	for(i=0; i<51; i++){
		*acRFiltre += hk[i] * at(dataBuffer, i).acr;
		*acIRFiltre += hk[i] * at(dataBuffer, i).acir;
	}

	return;
}



absorp firTest(char* str){
	absorp absorb;
	DataBuffer buffer;
	float acRPB, acRPBPrec, acIRPB, acIRPBPrec;
	char x, y;

	initDataBuffer(&buffer);

	FILE* pf = fopen(str, "r");
	if(!pf){
		printf("Le fichier n'a pu être lu.\n");
		return absorb;
	}

	do{
		fscanf(pf, "%f,%f,%f,%f,%c,%c", &absorb.acr, &absorb.dcr, &absorb.acir, &absorb.dcir, &x, &y);;

		if(!feof(pf)){
			push_front(&buffer, absorb);
			acRPBPrec = acRPB;
			acIRPBPrec = acIRPB;

			fir(&buffer, &acRPB, &acIRPB);

			absorb.acr = acRPB;
			absorb.acir = acIRPB;
		}
	}while(!feof(pf));


	return absorb;
}

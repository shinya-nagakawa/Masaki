#include "CXModelLoader.h"

int CXFrame::frameCont = 0;

static char str[255]="";
#define SCAN_DATA(fp,str,format,...) {	\
	fgets(str,255,fp);							\
	sscanf_s(str,format,__VA_ARGS__);				\
}												\

/*
  �����񂩂�;"���폜
*/
static void cutSymbol(char *src,char *dst){
	while(*src) {
		if(*src != ';' && *src != '\"') *dst++=*src++;
		else src++;
	}
	*dst = '\0';
}
/*
  �g�[�N���@���O ��ǂݍ���
*/
static void readToken(FILE *fp,char* token,char* name)
{
	token[0] = '\0';
	name[0] = '\0';
	SCAN_DATA(fp,str,"%s %s\n",token,64,name,64);	
}
/*
  �g�[�N�� ��ǂݍ���
*/
static void readToken(FILE *fp,char* token)
{
	token[0] = '\0';
	while(fscanf_s(fp,"%s",token,64) == 0 && !feof(fp));
}
/*
/*
 ����̕����񂪏o������܂Ńt�@�C���|�C���^��i�߂�
*/
static void forwardFilePointer(FILE *fp,char c)
{
	while(getc(fp) != c);
}
/*
 �v�f�̓ǂݍ��݂��΂�
*/
static void skipToken(FILE *fp) {
	char token[64]="";
	char name[64]="";
	while(!feof(fp)) {
		readToken(fp,token);
		if(strcmp(token,"{")==0) {
			skipToken(fp);
		}
		if(strcmp(token,"}")==0) {
			return;
		}
	}
}
/*
  �}�g���b�N�X�̓ǂݍ���
*/
static void readMatrix(FILE *fp,CXFrame *f) {
	CMatrix m;
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
	for(int i=0;i<4;i++) {
		SCAN_DATA(fp,str,"%f,%f,%f,%f,\n",&m.m[i][0],&m.m[i][1],&m.m[i][2],&m.m[i][3]);
	}
	fgets(str,255,fp); //�@}��΂�

	f->SetMatrix(m);
	
}

CXFrame* CXFrame::GetFrameByName_r(const char *name,CXFrame *f){
	CXFrame *find=NULL;
	if(strcmp(f->GetName(),name) == 0) return f;
	if(f->GetChild()) find=CXFrame::GetFrameByName_r(name,f->GetChild());
	if(f->GetNext() && !find) find=CXFrame::GetFrameByName_r(name,f->GetNext());
	return find;
}
CXFrame* CXFrame::GetFrameByName(const char *name,CXFrame *f){
	CXFrame *pRoot=f;
	while(pRoot->GetParent()) pRoot = pRoot->GetParent();

	return GetFrameByName_r(name,pRoot);
}
CXFrame* CXFrame::GetFrameByNo_r(const int no,CXFrame *f){
	CXFrame *find=NULL;
	if(f->GetNo() == no) return f;
	if(f->GetChild()) find=CXFrame::GetFrameByNo_r(no,f->GetChild());
	if(f->GetNext() && !find) find=CXFrame::GetFrameByNo_r(no,f->GetNext());
	return find;
}
CXFrame* CXFrame::GetFrameByNo(const int no,CXFrame *f){
	CXFrame *pRoot=f;
	while(pRoot->GetParent()) pRoot = pRoot->GetParent();

	return GetFrameByNo_r(no,pRoot);
}

void CXFrame::printFrame(CXFrame *f,int level){
	for(int i=0;i<level;i++) printf(" ");
	printf("%s %s No%d\n",f->GetToken(),f->GetName(),f->GetNo());
	if(f->GetChild()) printFrame(f->GetChild(),level+1);
	if(f->GetNext()) printFrame(f->GetNext(),level);
}
void CXFrame::printMatrix(CXFrame *f){
	CMatrix m = f->GetMatrix();
	printf("%s %s No%d\n"
		   " %f %f %f %f\n"
		   " %f %f %f %f\n"
		   " %f %f %f %f\n"
		   " %f %f %f %f\n",f->GetToken(),f->GetName(),f->GetNo(),
		   m.m00,m.m01,m.m02,m.m03,
		   m.m10,m.m11,m.m12,m.m13,
		   m.m20,m.m21,m.m22,m.m23,
		   m.m30,m.m31,m.m32,m.m33);
	if(f->GetChild()) printMatrix(f->GetChild());
	if(f->GetNext()) printMatrix(f->GetNext());
}

void CXFrame::release(){
	if(GetChild()) GetChild()->release();
	if(GetNext()) GetNext()->release();
	delete this;
}

CXMaterial::CXMaterial(FILE *fp){
	char tmp[MAX_STRINGS];
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
	SCAN_DATA(fp,str,"%f;%f;%f;%f;;",&faceColor.r,&faceColor.g,&faceColor.b,&faceColor.a);
	SCAN_DATA(fp,str,"%f;",&power);
	SCAN_DATA(fp,str,"%f;%f;%f;;",&specularColor.r,&specularColor.g,&specularColor.b);
	SCAN_DATA(fp,str,"%f;%f;%f;;",&emissiveColor.r,&emissiveColor.g,&emissiveColor.b);
	//SCAN_DATA(fp,str,"%s",tmp,MAX_STRINGS);
	fscanf_s(fp, "%s", tmp, MAX_STRINGS);
	if(strcmp(tmp,"TextureFilename")==0){
		forwardFilePointer(fp,'\"');
		for(int i=0;i<MAX_STRINGS;i++) {
			int c = getc(fp);
			if(c == '\"') {
				filename[i] = '\0';
				break;
			}
			filename[i] = c;
		}
		forwardFilePointer(fp,'}');
		fgets(str,255,fp); //}�Ƃ΂�
	} else {
		filename[0] = '\0';
	}
	fgets(str,255,fp); //}�Ƃ΂�
}
CXMeshTextureCoords::CXMeshTextureCoords(FILE *fp) {
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
	SCAN_DATA(fp,str,"%d;",&nTextureCoords);
	textureCoords = new SXTexCode2[nTextureCoords];
	for(int i=0;i<nTextureCoords;i++) {
		SCAN_DATA(fp,str,"%f;%f;,",&textureCoords[i].u,&textureCoords[i].v);
	}
	fgets(str,255,fp); //}�Ƃ΂�
}
CXMeshTextureCoords::~CXMeshTextureCoords() {
	SAFE_DELETE_ARRAY(textureCoords);
}
CXMeshMaterialList::CXMeshMaterialList(FILE *fp, CXModelLoader *myLoader){
	int k=0,j=0,i=0;
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
	SCAN_DATA(fp,str,"%d",&nMaterials);
	
	SCAN_DATA(fp,str,"%d",&nFaceIndexes);
	faceIndexes = new int[nFaceIndexes];
	for(i=0;i<nFaceIndexes;i++) {
		SCAN_DATA(fp,str,"%d",&faceIndexes[i]);
	}
	material = new char32[nMaterials];
	for(i=0;i<nMaterials;i++) {
		char token[64]="";
		char name[64]="";
		fscanf_s(fp,"%s",token,64);
//		sscanf_s(str,"%s %s",token,64,name,64);
		if(strcmp(token,"Material") == 0 ){
			fscanf_s(fp,"%s",name,64);
			//Mesh���Ƀ}�e���A������`����Ă���
			CXMaterial *m = new CXMaterial(fp);
			m->copyToken(token);
			m->copyName(name);
			myLoader->materials.push_back(m);
			strcpy_s(material[i],32,name);

		} else {
			//�t�@�C���̐擪�Ń}�e���A������`����Ă���ꍇ
			for(j=0,k=0;token[j]!='}';j++) {
				if(token[j]!='{' && token[j]!=' ') {
					material[i][k++]=token[j];
				}
			}
			material[i][k]='\0';
		}

	}
	
	forwardFilePointer(fp,'}');
	fgets(str,255,fp);
	//fgets(str,255,fp); //}�Ƃ΂�

}
CXMeshMaterialList::~CXMeshMaterialList() {
	SAFE_DELETE(faceIndexes);
	SAFE_DELETE_ARRAY(material);
}
CXMeshNormal::CXMeshNormal(FILE *fp) {
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
	SCAN_DATA(fp,str,"%d",&nNormals);

	normals = new SXVector3[nNormals];
	for(int i=0;i<nNormals;i++) {
		fgets(str,255,fp);
		sscanf_s(str,"%f;%f;%f;,",&normals[i].x,&normals[i].y,&normals[i].z);
	}
	
	SCAN_DATA(fp,str,"%d",&nFaceNormals);

	faceNormals = new SXIndex3[nFaceNormals];
	for(int i=0;i<nFaceNormals;i++) {
		int dummy;
		SCAN_DATA(fp,str,"%d;%d,%d,%d;,",&dummy,&faceNormals[i].idx[0],&faceNormals[i].idx[1],&faceNormals[i].idx[2]);
	}
	fgets(str,255,fp); //}�Ƃ΂�
}
CXMeshNormal::~CXMeshNormal(){	
	SAFE_DELETE_ARRAY(normals);
	SAFE_DELETE_ARRAY(faceNormals);
}
CXSkinWeights::CXSkinWeights(FILE *fp) {
	char tmp[MAX_STRINGS];
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
	SCAN_DATA(fp,str,"%s",tmp,MAX_STRINGS);
	cutSymbol(tmp,transformNodeName);
	SCAN_DATA(fp,str,"%d;",&nWeights);

	if(nWeights==0) {
		vertexIndices=NULL;
		weights = NULL;
	} else {
		vertexIndices=new int[nWeights];
		weights=new float[nWeights];
		for(int i=0;i<nWeights;i++) {
			SCAN_DATA(fp,str,"%d",&vertexIndices[i]);
		}
		for(int i=0;i<nWeights;i++) {
			SCAN_DATA(fp,str,"%f",&weights[i]);
		}
	}
	for(int i=0;i<4;i++) {
		char *tmp=str;
		SCAN_DATA(fp,str,"%f,%f,%f,%f,\n",&matrixOffset.m[i][0],&matrixOffset.m[i][1],&matrixOffset.m[i][2],&matrixOffset.m[i][3]);
		if(i==0) {
			//;�Ƃ΂�
			while(*tmp) {
				if(*tmp++==';') {
					i--;
					break;
				}
			}
		}
	}
	fgets(str,255,fp); //}�Ƃ΂�
}

CXSkinWeights::~CXSkinWeights() {
	SAFE_DELETE_ARRAY(vertexIndices);
	SAFE_DELETE_ARRAY(weights);
}

void CXLMesh::loadVertexData(FILE *fp) {

	SCAN_DATA(fp,str,"%d",&nVertices);

	vertices = new SXVector3[nVertices];
	for(int i=0;i<nVertices;i++) {
		SCAN_DATA(fp,str,"%f;%f;%f;,",&vertices[i].x,&vertices[i].y,&vertices[i].z);
	}
	
	SCAN_DATA(fp,str,"%d",&nFaces);

	faces = new SXIndex3[nFaces];
	for(int i=0;i<nFaces;i++) {
		int dummy;
		SCAN_DATA(fp,str,"%d;%d,%d,%d;,",&dummy,&faces[i].idx[0],&faces[i].idx[1],&faces[i].idx[2]);
	}
}

CXLMesh::CXLMesh(){	
	SetType(eMesh);
	vertices = NULL;
	faces = NULL;
	nVertices = 0;
	meshMaterialList = NULL;
	meshNormal = NULL;
	meshTextureCoords = NULL;
}
CXLMesh::~CXLMesh(){
	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE_ARRAY(faces);
	SAFE_DELETE(meshNormal);
	SAFE_DELETE(meshMaterialList);
	SAFE_DELETE(meshTextureCoords);
	for(std::vector<CXSkinWeights*>::iterator it=skinweights.begin();it!=skinweights.end();it++){
		SAFE_DELETE(*it);
	}
	skinweights.clear();		
}
void CXLMesh::loadFile(FILE *fp, CXModelLoader *myLoader) {
	
	char token[MAX_STRINGS];
//	char name[MAX_STRINGS];
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);

	loadVertexData(fp);
	while(1) {
		//fscanf_s(fp,"%s ",token);
		readToken(fp,token);
		if(strcmp(token,"MeshTextureCoords")==0) {
			meshTextureCoords = new CXMeshTextureCoords(fp);
		}else
		if(strcmp(token,"MeshNormals")==0) {
			meshNormal = new CXMeshNormal(fp);
		} else if(strcmp(token,"SkinWeights")==0) {
			CXSkinWeights *sw = new CXSkinWeights(fp);
			skinweights.push_back(sw);

		} else 
		if(strcmp(token,"MeshMaterialList")==0) {
			meshMaterialList = new CXMeshMaterialList(fp,myLoader);
		} else
		if(strcmp(token,"}")==0) {
			fgets(str,255,fp); // }�Ƃ΂�
			break;
		} else {
			forwardFilePointer(fp,'{');
			skipToken(fp);
		}
	}


}
CXAnimationKey::CXAnimationKey(FILE *fp) {
	char token[32];
	keys = NULL;
	while(1) {
		SCAN_DATA(fp,str,"%d;",&keyType);
		SCAN_DATA(fp,str,"%d;",&nKeys);
		if(!keys) keys = new CXTimedFloatKeys[nKeys];
		int dummy;
		float x,y,z,w;
		for(int i=0;i<nKeys;i++) {
			CMatrix tmp,matRX,matRY,matRZ;
			fscanf_s(fp,"%d;%d;\n",&keys[i].time,&dummy);
			switch(keyType) {
			// Rotation
			case 0:
				SCAN_DATA(fp,str,"%f,%f,%f,%f,\n",&w,&x,&y,&z);
				tmp.SetQuaternion(x,y,z,w);
				tmp = tmp.GetTranspose();
				/*
				matRX.RotationX(x);
				matRY.RotationY(y);
				matRZ.RotationZ(z);
				tmp = matRZ*matRY*matRX;
				*/
				keys[i].matrix = tmp * keys[i].matrix;
				break;
			//Scale
			case 1:
				SCAN_DATA(fp,str,"%f,%f,%f,\n",&x,&y,&z);
				tmp.Scale(x,y,z);
				keys[i].matrix = tmp * keys[i].matrix;


				break;
			//Position
			case 2:
				SCAN_DATA(fp,str,"%f,%f,%f,\n",&x,&y,&z);
				tmp.Transelate(x,y,z);
				keys[i].matrix = tmp * keys[i].matrix;

				break;
			//Matrix
			case 4:
				for(int j=0;j<4;j++) {
					SCAN_DATA(fp,str,"%f,%f,%f,%f,\n",	&keys[i].matrix.m[j][0],
														&keys[i].matrix.m[j][1],
														&keys[i].matrix.m[j][2],
														&keys[i].matrix.m[j][3]);
				}
				break;
			default:
				fgets(str,255,fp); // �Ƃ΂�
				break;
			}
		}
		fgets(str,255,fp); // }�Ƃ΂�
		fscanf_s(fp,"%s",token,32);
		//AnimationKey�ēǂݍ���
		if(strcmp(token,"AnimationKey")==0) {
			fgets(str,255,fp); // {�Ƃ΂�
			continue;
		}
		break;
	}
}
CXAnimationKey::~CXAnimationKey(){
	SAFE_DELETE_ARRAY(keys);
}
CXLAnimation::CXLAnimation(FILE *fp) {
	
	forwardFilePointer(fp,'{');
	fgets(str,255,fp); // {�Ƃ΂�
	//�{�[�����ǂݍ���
	fgets(str,255,fp);
//	fgets(str,255,fp);
	int i,k;
	//�{�[�����擾
	for(i=0,k=0;str[i]!='}';i++) {
		if(str[i]!='{' && str[i]!=' ') {
			boneName[k++]=str[i];
		}
	}
	boneName[k]='\0';

	// AnimationKey�Ƃ΂�
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
//	fgets(str,255,fp);

	animationkey = new CXAnimationKey(fp);
//	fgets(str,255,fp); // }�Ƃ΂�
}
CXLAnimation::~CXLAnimation(){
	SAFE_DELETE(animationkey);
}
CXAnimationSet::CXAnimationSet(FILE *fp) {
	char token[MAX_STRINGS];
//	char name[MAX_STRINGS];
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
//	fgets(str,255,fp); // {�Ƃ΂�
	while(1) {
		readToken(fp,token);
		if(strcmp(token,"Animation")==0) {
			CXLAnimation *a = new CXLAnimation(fp);
			animations.push_back(a);
		}else
		if(strcmp(token,"}")==0) {
			fgets(str,255,fp);
			break;
		}

	}

}
CXAnimationSet::~CXAnimationSet(){
	for(std::vector<CXLAnimation*>::iterator it=animations.begin();it!=animations.end();it++){
		SAFE_DELETE(*it);
	}
	animations.clear();
}
CXFrame* CXModelLoader::readFrame(FILE *fp,CXFrame *f) {
	char token[64]="";
	char name[64]="";
	CXFrame *pTmpChild=NULL;
	
	forwardFilePointer(fp,'{');
	fgets(str,255,fp);
	while(!feof(fp)) {
		//strcpy(token[1],token[0]);
		//strcpy(name[1],name[0]);
		//readToken(fp,token[0],name[0]);
		readToken(fp,token);
		if(strcmp(token,"FrameTransformMatrix")==0) {
			readMatrix(fp,f);
		}else
		if(strcmp(token,"Frame")==0) {
			readToken(fp,name);
			CXFrame *c = new CXFrame(token,name,CXFrame::GetFrameNomber());
			if(!f->GetChild()) f->SetChild(c);
			c->SetParent(f);
			if(pTmpChild) {
				pTmpChild->SetNext(c);
				c->SetPrev(pTmpChild);
			}
			pTmpChild = readFrame(fp,c);
		}else
		if(strcmp(token,"Mesh")==0) {
			CXLMesh *m = new CXLMesh(*f);
			delete f;
			f=m;
			m->loadFile(fp,this);
			mesh.push_back(m);
		}else
		if(strcmp(token,"}")==0) {
			//���̍s��
			fgets(str,255,fp);
			break;
		} else {
			skipToken(fp);
		}
		
	}
	return f;

}

CXModelLoader::CXModelLoader(const char* filePath){
	strcpy_s(m_filePath, PATH_SIZE, filePath);
	pRoot = NULL;
	FILE* fp;
	int level = 0 ;
	fps = 60;
	fopen_s(&fp, filePath, "r");
	if(!fp) {
		printf("�t�@�C�����I�[�v���ł��܂���ł��� %s\n",filePath);
		return;
	}
	char token[64];
	char name[64];
	CXFrame::reSetFrameNomber();
	while(!feof(fp)) {
		readToken(fp,token);
		printf("token %s\n",token);
		if(strcmp(token,"template")==0) {
			//�e���v���[�g�͔�΂�
			forwardFilePointer(fp,'}');
		}else
		if(strcmp(token,"Frame")==0) {
			readToken(fp,name);
			pRoot = new CXFrame(token,name,CXFrame::GetFrameNomber());
			//readToken(fp,token,name);
			readFrame(fp,pRoot);
		}else
		if(strcmp(token,"Material")==0) {
			readToken(fp,name);
			CXMaterial *m = new CXMaterial(fp);
			m->copyToken(token);
			m->copyName(name);
			materials.push_back(m);
		}else
		if(strcmp(token,"AnimationSet")==0) {
			readToken(fp,name);
			CXAnimationSet *a = new CXAnimationSet(fp);
			a->copyToken(token);
			a->copyName(name);
			animationSet.push_back(a);
		}else
		if (strcmp(token, "AnimTicksPerSecond") == 0) {
			forwardFilePointer(fp, '{');
			fscanf_s(fp,"%f", &fps);
			forwardFilePointer(fp, '}');
		}
	}
	if(!pRoot) {
		printf("Frame�����݂��܂���%s\n",filePath);
		return;
	}


	fclose(fp);
	printf("\nprint frame\n\n");
	CXFrame::printFrame(pRoot,0);
	
	printf("animationSet %d\n",animationSet.size());
}

int CXModelLoader::GetMaterialNum(const char *name){
	for(unsigned int i=0;i<materials.size();i++) {
		if(strcmp(materials[i]->GetName(),name)==0) return i;
	}
	return -1;
}

int CXModelLoader::GetFrameNum(const char *name){
	CXFrame *f = CXFrame::GetFrameByName(name,pRoot);
	return f->GetNo();
}
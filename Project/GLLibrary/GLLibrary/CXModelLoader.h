/*
 ���t�@�C�����[�_�[
 ���t�@�C������f�[�^��ǂݍ���
*/
#pragma once
#include "GL.h"
#include "CMatrix.h"
#include "Vertex.h"

#include <vector>

#define MAX_STRINGS	64

#define SAFE_DELETE(x) if((x)) delete (x); (x)=NULL;
#define SAFE_DELETE_ARRAY(x) if((x)) delete[] (x); (x)=NULL;
class CXModelLoader;
/*
 �t���[���̎��
*/
enum E_FRAME_TYPE{
	eFrame,	//�ʏ�t���[��	
	eMesh,	//���b�V���t���[��
};
/*
 �t���[���N���X
 ���t�@�[�����̊K�w�\�������̂܂܍\�z
 [Frame]
*/
class CXFrame {
protected:
	char token[MAX_STRINGS];
	char name[MAX_STRINGS];
	int	 no;			//�t���[���ԍ�
	E_FRAME_TYPE  type;	//�t���[���̎��
	CMatrix matrix;	//[FrameTransformMatrix]



	CXFrame* pChild;	//�q�t���[��
	CXFrame* pParent;	//�e�t���[��
	CXFrame* pNext;		//�Z��t���[��
	CXFrame* pPrev;
	static int frameCont; //�t���[������

	
	static CXFrame* GetFrameByName_r(const char *name,CXFrame *f);
	static CXFrame* GetFrameByNo_r(const int no,CXFrame *f);
public:
	CXFrame() {
		SetType(eFrame);
		pChild  = NULL;
		pParent = NULL;
		pNext   = NULL;
		pPrev   = NULL;
	}
	CXFrame(char *t,char *n,int number) {
		SetType(eFrame);
		pChild  = NULL;
		pParent = NULL;
		pNext   = NULL;
		pPrev   = NULL;
		no = number;
		copyToken(t);
		copyName(n);
	}
	virtual ~CXFrame(){
	}
	char* GetToken() {return token;}
	void copyToken(const char* c) {
		strcpy_s(token,sizeof(token),c);
	}
	char* GetName() {return name;}
	void copyName(const char* c) {
		strcpy_s(name,sizeof(name),c);
	}
	CXFrame* GetChild() {return pChild;}
	void SetChild(CXFrame* p) {pChild = p;}
	CXFrame* GetParent() {return pParent;}
	void SetParent(CXFrame* p) {pParent = p;}
	CXFrame* GetNext() {return pNext;}
	void SetNext(CXFrame* p) {pNext = p;}
	CXFrame* GetPrev() {return pPrev;}
	void SetPrev(CXFrame* p) {pPrev = p;}
	void SetNo(int n) { no = n;}
	int GetNo() { return no;}
	void SetType(E_FRAME_TYPE t) { type = t;}
	E_FRAME_TYPE GetType() { return type;}

	
	void SetMatrix(CMatrix &m) {		
		matrix = m;
	}
	CMatrix GetMatrix() {		
		return matrix;
	}

	CXFrame(CXFrame &f) {
		pChild  = f.GetChild();
		pParent = f.GetParent();
		pNext   = f.GetNext();
		pPrev   = f.GetPrev();
		if(pParent && pParent->GetChild()==&f) pParent->SetChild(this);
		if(pChild) {
			pChild->SetParent(this);
			CXFrame *p = pChild->GetNext();
			while(p) {
				p->SetParent(this);
				p = p->GetNext();
			}
		}
		if(pNext) pNext->SetPrev(this);
		if(pPrev) pPrev->SetNext(this);
		SetNo(f.GetNo());
		SetMatrix(f.GetMatrix());
		SetType(f.GetType());
		copyToken(f.GetToken());
		copyName(f.GetName());
	}
	/*
	  ���O����t���[�����擾
	*/
	static CXFrame* GetFrameByName(const char *name,CXFrame *f);
	/*
	  �ԍ�����t���[�����擾
	*/
	static CXFrame* GetFrameByNo(const int no,CXFrame *f);

	static int GetFrameNomber(){
		return frameCont++;
	}
	static void reSetFrameNomber(){
		frameCont = 0;
	}
	void release();
	/*
	  �f�o�b�O�p
	*/
	static void printMatrix(CXFrame *f);
	static void printFrame(CXFrame *f,int level);
	virtual void draw(){};

};
/*
   [Material]
*/
class CXMaterial:public CXFrame{
public:
	SXColorRGBA	faceColor;
	float power;
	SXColorRGB	specularColor;
	SXColorRGB	emissiveColor;
	char filename[MAX_STRINGS];
public:
	CXMaterial(FILE *fp);

};


/*
  ���b�V���p�t���[��
*/

/*
  [MeshTextureCoords]
*/
class CXMeshTextureCoords{
public:
	int nTextureCoords;
	SXTexCode2 *textureCoords;
public:
	CXMeshTextureCoords(FILE *fp);
	~CXMeshTextureCoords();
};
/*
  [MeshMaterialList]
*/
typedef char char32[32];
class CXMeshMaterialList {
public:
	int nMaterials;
	int nFaceIndexes;
	int *faceIndexes;
	char32 *material;
public:
	CXMeshMaterialList(FILE *fp, CXModelLoader *myLoader);
	~CXMeshMaterialList();
};
/*
  [SkinWeights]
*/
class CXSkinWeights {
public:
	char transformNodeName[32];
	int nWeights;
	int *vertexIndices;
	float *weights;
	CMatrix matrixOffset;
public:
	CXSkinWeights(FILE *fp);
	~CXSkinWeights();

};
/*
  [MeshNormals]
*/
class CXMeshNormal {
public:
	int nNormals;
	SXVector3 *normals;
	int nFaceNormals;
	SXIndex3 *faceNormals;
public:
	CXMeshNormal(FILE *fp);
	~CXMeshNormal();


};
/*
  [Mesh]
*/
class CXLMesh : public CXFrame{
public:
	int nVertices;
	SXVector3 *vertices;
	int nFaces;
	SXIndex3 *faces;


	CXMeshMaterialList *meshMaterialList;
	CXMeshNormal *meshNormal;
	CXMeshTextureCoords *meshTextureCoords;
	std::vector<CXSkinWeights*> skinweights;

	void loadVertexData(FILE *fp);

public:
	CXLMesh();
	~CXLMesh();
	CXLMesh(CXFrame &f) : CXFrame(f){
		SetType(eMesh);
		vertices = NULL;
		faces = NULL;
		nVertices = 0;
		meshMaterialList = NULL;
		meshNormal = NULL;
		meshTextureCoords = NULL;
	}
	void loadFile(FILE *fp, CXModelLoader *myLoader);
		
};


/*
  �A�j���[�V�����p
*/
class CXTimedFloatKeys {
public:
	int time;
	CMatrix matrix;
};
/*
  [AnimationKey]
*/
class CXAnimationKey {
public:
	int keyType;
	int nKeys;
	CXTimedFloatKeys *keys;
public:
	CXAnimationKey(){
		keys = NULL;
	}
	CXAnimationKey(CXAnimationKey &a){
		nKeys = a.nKeys;
		keyType = a.keyType;
		keys = new CXTimedFloatKeys[nKeys];
		memcpy(keys,a.keys,sizeof(CXTimedFloatKeys)*nKeys);
	}
	CXAnimationKey(FILE *fp);
	~CXAnimationKey();

};
/*
  [Animation]
*/
class CXLAnimation {
public:
	char boneName[64];
	CXAnimationKey *animationkey;
public:
	CXLAnimation(){
	}
	CXLAnimation(CXLAnimation &a){
		strcpy_s(boneName,sizeof(boneName),a.boneName);
		animationkey = new CXAnimationKey(*a.animationkey);
	}
	CXLAnimation(FILE *fp);
	~CXLAnimation();
};
/*
  [AnimationSet]
*/
class CXAnimationSet : public CXFrame{
public:
	std::vector<CXLAnimation*> animations;
public:
	CXAnimationSet(){
	}
	CXAnimationSet(CXAnimationSet &a){
		copyName(a.name);
		for(unsigned int i=0;i<a.animations.size();i++) {
			animations.push_back(new CXLAnimation(*a.animations[i]));
		}
	}
	CXAnimationSet(FILE *fp);
	~CXAnimationSet();
};
/*
  x�t�@�C������K�w�\���œǂݍ���
*/
class CXModelLoader {
public:
	//�t���[�����[�g
	CXFrame* pRoot;
	//���b�V�����X�g
	std::vector<CXLMesh*> mesh;  
	//�}�e���A�����X�g
	std::vector<CXMaterial*> materials; 
	//�A�j���[�V�������X�g
	std::vector<CXAnimationSet*> animationSet; 

	static const int PATH_SIZE = 256;
	char	m_filePath[PATH_SIZE];
	float	fps;
	CXFrame* readFrame(FILE *fp,CXFrame *f);

public:
	CXModelLoader(const char* filePath);
	~CXModelLoader() {
		if(pRoot) pRoot->release();	
		for(std::vector<CXMaterial*>::iterator it=materials.begin();it!=materials.end();it++){
			SAFE_DELETE(*it);
		}
		materials.clear();
		for(std::vector<CXAnimationSet*>::iterator it=animationSet.begin();it!=animationSet.end();it++){
			SAFE_DELETE(*it);
		}
		animationSet.clear();
	}
	/*
	  ���O����}�e���A���̔ԍ����擾
	*/
	int GetMaterialNum(const char *name);
	/*
	  ���O����t���[���̔ԍ����擾
	*/
	int GetFrameNum(const char *name);
	/*
	  �f�o�b�O�p
	*/
	static void printFrame(CXFrame *f,int level);
};

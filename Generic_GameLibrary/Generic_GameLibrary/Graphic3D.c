#include "Generic_GameLibrary.h"

/**
 * GglGraphic3d_Render関数
 * 指定されたGglModel構造体の3Dモデルを描画します
 * それぞれ原点から移動させたくない、回転させたくない、拡縮させたくない場合はNULLを入れます
 *
 * @param 描画したいモデル
 * @param 描画位置
 * @param モデル回転角
 * @param モデル拡縮
*/
void GglGraphic3d_Render(const GglModel* in_pModel, const GglVector3d* in_pTranslate, const GglVector3d* in_pRotate, const GglVector3d* in_pScale)
{
	GglMatrix4x4 mat;
	int i;

	if(!in_pModel)
	{
		return ;
	}


	// モデル行列初期化
	GglMatrix4x4_SetIdentity(&mat);

	// モデルのスケール行列を追加
	if(in_pScale)
	{
		GglMatrix4x4 buf = GglMatrix4x4_GetScale(in_pScale);
		GglMatrix4x4_Mul(&mat, &mat, &buf);
	}

	// モデルの回転行列を乗算
	if(in_pRotate)
	{
		GglMatrix4x4 buf;

		buf = GglMatrix4x4_GetRotateYaw(in_pRotate->z);
		GglMatrix4x4_Mul(&mat, &mat, &buf);
		buf = GglMatrix4x4_GetRotatePitch(in_pRotate->y);
		GglMatrix4x4_Mul(&mat, &mat, &buf);
		buf = GglMatrix4x4_GetRotateRoll(in_pRotate->x);
		GglMatrix4x4_Mul(&mat, &mat, &buf);
	}

	// モデルの位置行列を乗算
	if(in_pTranslate)
	{
		GglMatrix4x4 buf = GglMatrix4x4_GetTranslation(in_pTranslate);
		GglMatrix4x4_Mul(&mat, &mat, &buf);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadMatrixd(mat.array[0]);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	for(i=0; i<(int)in_pModel->face.max; i++)
	{
		if(in_pModel->face.index[i].useFourPolygon)
		{
			glBegin(GL_QUADS);

				// 色情報ロード
				glColor4fv(in_pModel->material.index[in_pModel->face.index[i].materialIndex].colorType.array);
			
				// マテリアル情報ロード
				glMaterialfv(GL_FRONT, GL_DIFFUSE, in_pModel->material.index[in_pModel->face.index[i].materialIndex].colorType.array);
				glMaterialfv(GL_FRONT, GL_SPECULAR, in_pModel->material.index[in_pModel->face.index[i].materialIndex].specularColor.array);
				glMaterialfv(GL_FRONT, GL_EMISSION, in_pModel->material.index[in_pModel->face.index[i].materialIndex].emissionColor.array);
				glMateriali(GL_FRONT, GL_SHININESS, in_pModel->material.index[in_pModel->face.index[i].materialIndex].lightPower);

				// 法線情報ロード
				glNormal3dv(in_pModel->face.normals[in_pModel->face.index[i].index[0]].array);
				glNormal3dv(in_pModel->face.normals[in_pModel->face.index[i].index[1]].array);
				glNormal3dv(in_pModel->face.normals[in_pModel->face.index[i].index[2]].array);
				glNormal3dv(in_pModel->face.normals[in_pModel->face.index[i].index[3]].array);

				// バーテクス情報ロード
				glVertex3dv(in_pModel->vertex.index[in_pModel->face.index[i].index[0]].array);
				glVertex3dv(in_pModel->vertex.index[in_pModel->face.index[i].index[1]].array);
				glVertex3dv(in_pModel->vertex.index[in_pModel->face.index[i].index[2]].array);
				glVertex3dv(in_pModel->vertex.index[in_pModel->face.index[i].index[3]].array);

				//// テクスチャ情報
				//if(in_pModel->face.index[i].useTexture)
				//{
				//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				//	glEnable(GL_TEXTURE_2D);
				//	
				//		glBindTexture(GL_TEXTURE_2D, in_pModel->face.index[i].uv);

				//	glDisable(GL_TEXTURE_2D);
				//}
				
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);

				// 色情報ロード
				glColor4fv(in_pModel->material.index[in_pModel->face.index[i].materialIndex].colorType.array);

				// マテリアル情報ロード
				glMaterialfv(GL_FRONT, GL_DIFFUSE, in_pModel->material.index[in_pModel->face.index[i].materialIndex].colorType.array);
				glMaterialfv(GL_FRONT, GL_SPECULAR, in_pModel->material.index[in_pModel->face.index[i].materialIndex].specularColor.array);
				glMaterialfv(GL_FRONT, GL_EMISSION, in_pModel->material.index[in_pModel->face.index[i].materialIndex].emissionColor.array);
				glMateriali(GL_FRONT, GL_SHININESS, in_pModel->material.index[in_pModel->face.index[i].materialIndex].lightPower);

				// 法線情報ロード
				glNormal3dv(in_pModel->face.normals[in_pModel->face.index[i].index[0]].array);
				glNormal3dv(in_pModel->face.normals[in_pModel->face.index[i].index[1]].array);
				glNormal3dv(in_pModel->face.normals[in_pModel->face.index[i].index[2]].array);

				// バーテクス情報ロード
				glVertex3dv(in_pModel->vertex.index[in_pModel->face.index[i].index[0]].array);
				glVertex3dv(in_pModel->vertex.index[in_pModel->face.index[i].index[1]].array);
				glVertex3dv(in_pModel->vertex.index[in_pModel->face.index[i].index[2]].array);

				//// テクスチャ情報
				//if(in_pModel->face.index[i].useTexture)
				//{
				//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				//	glEnable(GL_TEXTURE_2D);
				//	
				//		glBindTexture(GL_TEXTURE_2D, in_pModel->face.index[i].uv);

				//	glDisable(GL_TEXTURE_2D);
				//}

			glEnd();
		}
	}

	glPopMatrix();
	glDisable(GL_CULL_FACE);
	glLoadIdentity();

	return ;
}
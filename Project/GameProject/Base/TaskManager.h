#pragma once
#include<list>

/*Taskの管理 リスト関連*/

class Task;

class TaskManager {
public:
	/// <summary>
	/// タスクリストに追加
	/// </summary>
	/// <param name="add"></param>
	/// <param name="isShort"></param>
	/// <param name="layer">設定しない</param>
	/// 1つ目のレイヤーにのみ追加、レイヤーを切り替えることで2つ目のレイヤーになり、
	/// 2つ目のレイヤーには自身を追加していないので更新処理が呼ばれない
	static void AddtoTask(Task* add, bool isShort = false, int layer = 0);
	/// <summary>
	/// レンダーリストに追加
	/// </summary>
	/// <param name="add"></param>
	/// <param name="isShort"></param>
	static void AddtoRender(Task* add, bool isShort = false);
	/// <summary>
	/// コリジョンリストに追加
	/// </summary>
	/// <param name="add"></param>
	/// <param name="isShort"></param>
	static void AddtoCollision(Task* add, bool isShort = false);

	/// <summary>
	/// リストから削除
	/// </summary>
	/// <param name="remove"></param>
	/// <param name="isShort"></param>
	static void Remove(Task* remove, bool isShort = false);
	/// <summary>
	/// リストから削除しオブジェクトを削除
	/// </summary>
	/// <param name="del"></param>
	static void Delete(Task* del);
	/// <summary>
	/// 削除の確認
	/// </summary>
	static void DeleteChack();

	/// <summary>
	/// 全オブジェクト削除
	/// </summary>
	static void DeleteAll();
	/// <summary>
	/// 全てのオブジェクトの更新処理
	/// </summary>
	static void UpdateAll();
	/// <summary>
	/// 全てのオブジェクトの描画処理(画像)
	/// </summary>
	static void DrawAll();
	/// <summary>
	/// 全てのオブジェクトの描画処理
	/// </summary>
	static void RenderAll();
	/// <summary>
	/// 全てのオブジェクトの衝突判定
	/// </summary>
	static void CollisionAll();
	/// <summary>
	/// 全てのオブジェクトの削除
	/// </summary>
	static void KillAll();

	/// <summary>
	/// オブジェクトの検索
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static Task* FindObject(int type);
	/// <summary>
	/// オブジェクトの検索(配列を取得)
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static std::list<Task*> FindObjects(int type);
	/// <summary>
	/// オブジェクトの検索(最後に取得した要素を返却)
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static Task* FindObjectReverce(int type);
	/// <summary>
	/// IDでオブジェクトを検索
	/// </summary>
	/// <param name="ID">検索対象のID</param>
	/// <returns></returns>
	static Task* FindObjectbyID(unsigned int ID);

	/// <summary>
	/// オブジェクト毎にあった当たり判定を行う物のリストを返却
	/// </summary>
	/// <param name="self">自身</param>
	/// <returns></returns>
	static std::list<Task*> GetCollisionTargets(Task* self);
	/// <summary>
	/// レイヤーの変更(ポーズ機能)
	/// </summary>
	static void LayerChange();
	/// <summary>
	/// 現在のレイヤーを返却
	/// </summary>
	/// <returns></returns>
	static int GetLayer();
	/// <summary>
	/// 指定のタイプがインデックスを使用するか取得
	/// </summary>
	/// <param name="type">確かめたいタイプ</param>
	/// <returns></returns>
	static bool GetIndexFlag(int type);
	/// <summary>
	/// インデックスを使用するかをタイプ毎に設定
	/// </summary>
	static void SetIndexFlag();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TaskManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TaskManager();

	static int currentLayer;                 //現在扱っているタスクリストの
	static std::list<Task*> m_taskList[2];   //タスクのリスト
	static std::list<Task*> m_renderList;    //描画するオブジェクトのリスト
	static std::list<Task*> m_collisionList; //衝突判定を行うオブジェクトのリスト
	static std::list<Task*> m_cacheList;     //キャッシュのリスト
	static std::unordered_map<int, std::list<Task*>> m_index; //Typeをキーとしたインデックスのマップ
	static std::unordered_map<int, bool> m_indexFlag;         //Typeごとにインデックスを使用するかどうかを判別するマップ
};
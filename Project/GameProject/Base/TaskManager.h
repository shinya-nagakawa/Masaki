#pragma once
#include<list>

/*Taskの管理 リスト関連*/

class Task;

class TaskManager {
public:
	/// <summary>
	/// 自身を生成/返却(シングルトン)
	/// </summary>
	/// <returns>自身</returns>
	static TaskManager* GetInstance();
	/// <summary>
	/// 自身を削除
	/// </summary>
	static void Clearinstance();

	/// <summary>
	/// タスクリストに追加
	/// </summary>
	/// <param name="add">追加するタスク</param>
	/// <param name="layer">設定しない</param>
	/// 1つ目のレイヤーにのみ追加、レイヤーを切り替えることで2つ目のレイヤーになり、
	/// 2つ目のレイヤーには自身を追加していないので更新処理が呼ばれない
	void AddtoTask(Task* add, int layer = 0);
	/// <summary>
	/// レンダーリストに追加
	/// </summary>
	/// <param name="add">追加するタスク</param>
	void AddtoRender(Task* add);
	/// <summary>
	/// コリジョンリストに追加
	/// </summary>
	/// <param name="add">追加するタスク</param>
	void AddtoCollision(Task* add);

	/// <summary>
	/// リストから削除
	/// </summary>
	/// <param name="remove">削除するタスク</param>
	void Remove(Task* remove);
	/// <summary>
	/// リストから削除しオブジェクトを削除
	/// </summary>
	/// <param name="del">削除するタスク</param>
	void Delete(Task* del);
	/// <summary>
	/// 削除の確認
	/// </summary>
	void DeleteChack();

	/// <summary>
	/// 全オブジェクト削除
	/// </summary>
	void DeleteAll();
	/// <summary>
	/// 全てのオブジェクトの更新処理
	/// </summary>
	void UpdateAll();
	/// <summary>
	/// 全てのオブジェクトの描画処理(画像)
	/// </summary>
	void DrawAll();
	/// <summary>
	/// 全てのオブジェクトの描画処理(モデル)
	/// </summary>
	void RenderAll();
	/// <summary>
	/// 全てのオブジェクトの衝突判定
	/// </summary>
	void CollisionAll();
	/// <summary>
	/// 全てのオブジェクトの削除
	/// </summary>
	void KillAll();

	/// <summary>
	/// オブジェクトの検索(最初に見つかった要素を取得)
	/// </summary>
	/// <param name="type">検索するオブジェクトのタイプ</param>
	/// <returns>検索結果</returns>
	Task* FindObject(int type);
	/// <summary>
	/// オブジェクトの検索(配列を取得)
	/// </summary>
	/// <param name="type">取得するオブジェクトのタイプ</param>
	/// <returns></returns>
	std::list<Task*> FindObjects(int type);
	/// <summary>
	/// オブジェクトの検索(最後に見つかった要素を取得)
	/// </summary>
	/// <param name="type">検索するオブジェクトのタイプ</param>
	/// <returns>検索結果</returns>
	Task* FindObjectReverce(int type);
	/// <summary>
	/// IDでオブジェクトを検索
	/// </summary>
	/// <param name="ID">検索対象のID</param>
	/// <returns>検索結果</returns>
	Task* FindObjectbyID(unsigned int ID);

	/// <summary>
	/// オブジェクト毎にあった当たり判定を行う物のリストを返却
	/// </summary>
	/// <param name="self">自身</param>
	/// <returns>当たり判定を行うオブジェクトがまとめられたリスト</returns>
	std::list<Task*> GetCollisionTargets(Task* self);
	/// <summary>
	/// レイヤーの変更(ポーズ機能)
	/// </summary>
	void LayerChange();
	/// <summary>
	/// 現在のレイヤーを返却
	/// </summary>
	/// <returns>現在のレイヤー</returns>
	int GetLayer() const;
	/// <summary>
	/// 指定のタイプがインデックスを使用するか取得
	/// </summary>
	/// <param name="type">確かめたいタイプ</param>
	/// <returns>インデックスを使用するタイプか</returns>
	bool GetIndexFlag(int type);
	/// <summary>
	/// インデックスを使用するかをタイプ毎に設定
	/// </summary>
	void SetIndexFlag();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TaskManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TaskManager();

private:
	static TaskManager* instance;     //インスタンス

	int currentLayer;                 //現在扱っているタスクリストの番号
	std::list<Task*> m_taskList[2];   //タスクのリスト
	std::list<Task*> m_renderList;    //描画するオブジェクトのリスト
	std::list<Task*> m_collisionList; //衝突判定を行うオブジェクトのリスト
	std::list<Task*> m_cacheList;     //キャッシュのリスト
	std::unordered_map<int, std::list<Task*>> m_index; //Typeをキーとしたインデックスのマップ
	std::unordered_map<int, bool> m_indexFlag;         //Typeごとにインデックスを使用するかどうかを判別するマップ
};
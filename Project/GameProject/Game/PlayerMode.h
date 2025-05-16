#pragma once
#include "Player.h"

/*プレイヤーの各モードの処理の実装に使うクラス*/

class PlayerMode {
public:
    virtual ~PlayerMode() {}
    /// <summary>
    /// プレイヤーを取得
    /// </summary>
    /// <returns>プレイヤー</returns>
    Player* GetPlayer(){
        return mp_player;
    }
    /// <summary>
    /// プレイヤーを設定
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void SetPlayer(Player* player) {
        mp_player = player;
    }

    //開始時処理
    virtual void Enter() = 0;
    // モードごとの更新処理
    virtual void Update() = 0;
    // モードごとの描画処理
    virtual void Render() {}
    //終了時処理
    virtual void Exit() = 0;

    /// <summary>
    /// 状態遷移
    /// </summary>
    /// <param name="state">変更する状態</param>
    virtual void ChangeState(Player::PlayerState state) = 0;

protected:
    Player* mp_player = nullptr; //プレイヤー
};
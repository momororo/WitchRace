//
//  Zorder.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/04.
//
//

/**
 *  zOrderを一括管理します。
 *  スプライトにzPositionを設定する際は、ここでdefine後、当ファイルをincludeして使ってください。
 */
#ifndef WitchRace_Zorder_h
#define WitchRace_Zorder_h

/**
 *  zPosition一覧
 */

//staticBackGround
#define zOrderOfStaticBackGround 0
//背景
#define zOrderOfBackGround 10

//キキ
#define zOrderOfKiki 100
//こうもり
#define zOrderOfBad 100

#endif

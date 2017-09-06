/**
* @file      AppUi.h
* @brief     in this file function math defined.
* @details   
* @author    zy
* @date      2017/07/11
* @version   HMI-T001
* @par Copyright (c)
*      keluofeite
* @par History:
*
*   version: author, date, desc\n
*/
#ifndef H_APPUI_SDK
#define H_APPUI_SDK

/**This is the brief of the PageUpTurn
*	int PageUpTurn()
*   this function can realise the turn up of the page.
*	@param have no parama.
*	@retval  int
*	@return  on success 0 is returnee. On error, -1 is returned.
*	@see	 ////
*	@note	 
*/
int PageUpTurn();

/**This is the brief of the PageDownturn
*	int PageDownturn()
*	this function can realise the turn down of the page.
*	@param have no parama.
*	@retval  int
*	@return  on success 0 is returnee. On error, -1 is returned.
*	@see	 ////
*	@note	 
*/
int PageDownTurn();

/**This is the brief of the PageHometurn
*	int PageHomeTurn()
*	this function can realise the turn up of the page.
*	@param have no parama.
*	@retval  int
*	@return  on success 0 is returnee. On error, -1 is returned.
*	@see	 ////
*	@note	 
*/
int PageHomeTurn();

/**This is the brief of the PageUpdate
* 	int PageUpdate(char *data);
*   this function can update the page data from data. the data format should be 
*   "name=yidali|personid=123456|date=20170722|nursetype=first|checkdate=20170722|
*   medicine=arcg|doctorname=sony", the  symbol "=" you can change for update.
*	the functions will return a number.
*	@param   data is the information you want to update.
*   @retval  int
*   @return  on success 0 is returned. On error, -1 is returned.
*	@see     ////
*   @note    
*/
int PageUpdate(char *data);

#endif

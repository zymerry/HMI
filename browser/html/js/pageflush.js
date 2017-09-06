$(function() {
	
	// 定时器句柄
	var show_timer;

	// 定时器函数
	function timerfunc()
	{
		/* pageflush('{ "hardver": "v1.0.3", "softver": "v1.0.3"}'); */
		// 获取JSON数据
		var str = fancy.getMsg();
        // fancy.print(str);
		/* alert(str); */
		
		// 处理JSON数据
		msgFactory(str);
	}
	
	function msgFactory(msg)
	{
		// 判断字符串长度是否合法
		if ( 0 == msg.length )
		{
			return;
		}
		
		// 解析JSON格式的数据
		var obj = jQuery.parseJSON(msg);
		/* alert(obj.cmd); */
        // fancy.print(obj.cmd);
		
		// 判断消息类型
		switch(obj.cmd)
		{
			case "PageUpTurn":
			{
				pageTurn("Up");
			}
			break;
			
			case "PageDownTurn":
			{
				pageTurn("Down");
			}
			break;
			
			case "PageHomeTurn":
			{
				pageTurn("Home");
			}
			break;
			
			case "PageFlush":
			{
				pageflush(obj.data);
			}
			break;
		}
	}
	
	function getCurrentPageNum()
	{
		var filename = window.location.pathname;
/* 		alert(filename.lastIndexOf('/'));
		alert(filename.indexOf('/'));
		alert(fancy.indexOf(filename, "/"));
		alert(fancy.lastIndexOf(filename, "/")); */
		filename = filename.substr(fancy.lastIndexOf(filename, '/')+1);
		var num = filename.substr(0, fancy.lastIndexOf(filename, '.'));
		return parseInt(num);
	}
	
	function fileIsExist()
	{
		return true;
	}
	
	// 页面刷新函数
	function pageflush(obj)
	{
		// 遍历JSON数据的内容
		for (var key in obj)
		{
/* 			alert(key);
			alert(obj[key]); */
			
			inputID="#"+key;
			/* $(inputID).attr("value", obj[key]); */
			$(inputID).html(obj[key]);
		}
		
		// 获取JSON所有的Key
/* 		alert(Object.keys(obj)); */		
	}
	
	// 翻页函数
	function pageTurn(direction)
	{
        // fancy.print("pageTurn");
		switch(direction)
		{
			case "Up":
			{
                var cnum = fancy.getCurrentPageNum();

                var hideID = "#"+cnum;
                cnum -= 1;
                var showID = "#"+cnum;

                if ( $(showID).length <= 0 )
                {
                    return;
                }

                $(hideID).hide();
                $(showID).show();
                fancy.setCurrentPageNum(cnum);
				// var cnum = getCurrentPageNum();
				// cnum -= 1;
				// 
				// var htmlname = cnum+".html";
				// // alert(htmlname);
				// 
				// // 打开本地网页
				// window.location = htmlname;
				// // fancy.load(htmlname);
			}
			break;
			case "Down":
			{
                var cnum = fancy.getCurrentPageNum();

                var hideID = "#"+cnum;
                cnum += 1;
                var showID = "#"+cnum;

                if ( $(showID).length <= 0 )
                {
                    return;
                }

                $(hideID).hide();
                $(showID).show();
                fancy.setCurrentPageNum(cnum);
				// var cnum = getCurrentPageNum();
				// cnum += 1;
				// 
				// var htmlname = cnum+".html";
				// // alert(htmlname);
				// 
				// // 打开本地网页
				// window.location = htmlname;
				// // fancy.load(htmlname);
			}
			break;
			case "Home":
			{
                var cnum = fancy.getCurrentPageNum();

                hideID = "#"+cnum;
                cnum = 1;
                showID = "#"+cnum;

                $(hideID).hide();
                $(showID).show();
                fancy.setCurrentPageNum(cnum);

                // var cnum = getCurrentPageNum();
                // if ( 1 == cnum )
                // {
                //     return;
                // }
				// var cnum = "1";				
				// var htmlname = cnum+".html";
				// // alert(htmlname);
				// 
				// // 打开本地网页
				// window.location = htmlname;
				// // fancy.load(htmlname);
			}
			break;
		}
	}
	
	$(document).ready(function(){
		
/* 		fancy.print( 'Test Page for Qt Javascript Extension!' ); 
		
		// 更新HTML内容
		$("#hardver").attr("value", "v1.0.1");
		$("#softver").attr("value", "v1.0.1");
		
		alert("flush");
		// 使用变量直接作为ID更新HTML内容
		var inputID = "#hardver";
		$(inputID).attr("value", "v1.0.2");
		var inputID = "#softver";
		$(inputID).attr("value", "v1.0.2");
		
		// 解析JSON格式的数据
		var obj = jQuery.parseJSON('{ "hardver": "v1.0.3", "softver": "v1.0.3"}');
		// 遍历JSON数据的内容
		for (var key in obj)
		{
			alert(key);
			alert(obj[key]);
			
			inputID="#"+key;
			$(inputID).attr("value", obj[key]);
		}
		
		// 获取JSON所有的Key
		alert(Object.keys(obj)); */
		
        // fancy.print("on windows: "+window.location.pathname);
        $("#1").show();
        $("#2").hide();
        $("#3").hide();
		timerfunc();
		clearInterval(show_timer);
		show_timer = setInterval(timerfunc, 100);
		
		/* alert($("#name").is("span")); */
		/* $("#name").attr("value", "韩梅梅"); */
		/* $("#name").html("韩梅梅"); */
		/* document.getElementById("name").innerHTML = "韩梅梅"; */
	});
	
})

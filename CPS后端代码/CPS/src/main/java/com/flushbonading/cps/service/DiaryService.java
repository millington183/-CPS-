package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Diary;
import com.flushbonading.cps.entity.vo.DiaryDataVO;

import java.util.List;
import java.util.Map;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
public interface DiaryService extends IService<Diary> {
    /**
     * 查询每一时段内的具体信息
     *
     * @return 返回时间段对应的
     */
    List<Map<String, Object>> queryDiary();

    /**
     * 清除上一天的数据
     *
     * @return
     */
    Integer updateCounts();

    /**
     * 得到每时段产量
     *
     * @return
     */
    List<DiaryDataVO> getDiaryDataVos();
}

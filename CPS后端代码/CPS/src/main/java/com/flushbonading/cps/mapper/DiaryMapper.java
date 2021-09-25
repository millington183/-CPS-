package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Diary;
import com.flushbonading.cps.entity.vo.DiaryDataVO;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Mapper
public interface DiaryMapper extends BaseMapper<Diary> {
    /**
     * 增加一个产品
     *
     * @param equipmentId
     * @param timeId
     * @return
     */
    Integer increase(String equipmentId, String timeId);

    /**
     * 清空所有产品
     *
     * @return
     */
    Integer updateCounts();

    List<DiaryDataVO> getDiaryDataVos();
}

package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Material;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.vo.MaterialVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-17
 */
public interface MaterialService extends IService<Material> {
    /**
     * 显示物料
     *
     * @param materialId
     * @param page
     * @return
     */
    List<MaterialVO> showMaterials(String materialId, Integer page);

    /**
     * 物料总数
     *
     * @param materialId
     * @return
     */
    Integer materialCounts(String materialId);

    /**
     * 页面数
     *
     * @param materialId
     * @return
     */
    Integer totalPages(String materialId);

    /**
     * 增加一个物料
     *
     * @param material
     * @return
     */
    RespBean addAMaterial(MaterialVO material);

    /**
     * 通过物料id删除物料
     *
     * @param materialId
     * @return
     */
    RespBean deleteAMaterialByMaterialId(String materialId);

    /**
     * 修改物料详细信息
     *
     * @param material
     * @return
     */
    RespBean updateAMaterial(MaterialVO material);

    /**
     * 得到所有物料名称
     *
     * @return
     */
    List<String> getBrandName();
}
